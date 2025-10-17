// algo.tpp

#include "header.hpp"

template <typename T> std::ostream &operator<<(std::ostream &os, const std::vector<T> &v) {
  typename std::vector<T>::const_iterator it = v.begin();
  while (it != v.end()) {
    os << *it;
    ++it;
    if (it != v.end())
      os << " ";
  }
  return os;
}

template <typename T> std::ostream &operator<<(std::ostream &os, const std::deque<T> &d) {
  typename std::deque<T>::const_iterator it = d.begin();
  while (it != d.end()) {
    os << *it;
    ++it;
    if (it != d.end())
      os << " ";
  }
  return os;
}

template <typename Container> void parse(const char **av, Container &numbers) {
  Container dup;

  if (!av[2]) {
    const char *str = av[1];

    while (*str) {
      char *e;
      size_t n = strtol(str, &e, 10);

      if (str == e)
        break;

      if (std::find(numbers.begin(), numbers.end(), n) != numbers.end())
        throw std::runtime_error("Error: duplicate number");

      numbers.push_back(n);
      dup.push_back(n);

      str = e;
    }
    return;
  }

  for (int i = 1; av[i]; i++) {

    char *endp;
    long n = strtol(av[i], &endp, 10);

    if (n < 0)
      throw std::runtime_error("Error: negative number");

    if (*endp != 0)
      throw std::runtime_error("Error: invalid input");

    if (std::find(numbers.begin(), numbers.end(), n) != numbers.end())
      throw std::runtime_error("Error: duplicate number");

    numbers.push_back(n);
    dup.push_back(n);
  }
}

template <typename Container> Container jacobsthal(size_t n) {
  Container j;
  j.push_back(0);
  j.push_back(1);

  for (size_t i = 2; i < 50; i++) {
    size_t next = (2 * (j[i - 2])) + j[i - 1];
    if (next > n)
      break;
    j.push_back(next);
  }

  j.erase(j.begin() + 1);

  return j;
}

template <typename Container> Container jacobsthalOrdering(size_t n, size_t size) {
  Container indices;
  Container j = jacobsthal<Container>(n);

  for (size_t i = 0; i < j.size(); ++i) {
    if (j[i] < n)
      indices.push_back(j[i]);
  }

  for (size_t i = 0; i < n; ++i) {
    if (std::find(j.begin(), j.end(), i) == j.end()) {
      indices.push_back(i);
    }
  }

  if (indices.size() == (size - n - 1)) {
    indices.push_back(n);
  }

  return indices;
}
template <typename Container> Container fordJohnsonSortMaxima(const Container &maxima) {
  if (maxima.size() <= 1)
    return maxima;

  size_t mid = maxima.size() / 2;

  Container left(maxima.begin(), maxima.begin() + mid);
  Container right(maxima.begin() + mid, maxima.end());

  left = fordJohnsonSortMaxima(left);
  right = fordJohnsonSortMaxima(right);

  Container merged;
  std::merge(left.begin(), left.end(), right.begin(), right.end(), std::back_inserter(merged), Counter());

  return merged;
}

template <typename BoolContainer, typename Container, typename PairContainer> void sort(PairContainer &initialPairs, Container &chain, size_t size) {

  if (initialPairs.size() == 1) {
    chain.push_back(initialPairs[0].first);
    chain.push_back(initialPairs[0].second);
    return;
  }

  Container maxima;
  for (size_t i = 0; i < initialPairs.size(); ++i)
    maxima.push_back(initialPairs[i].second);

  Container sortedMaxima = fordJohnsonSortMaxima(maxima);

  PairContainer sortedPairs;
  BoolContainer used(initialPairs.size(), false);

  for (size_t i = 0; i < sortedMaxima.size(); ++i) {
    size_t m = sortedMaxima[i];
    for (size_t j = 0; j < initialPairs.size(); ++j) {
      if (!used[j] && initialPairs[j].second == m) {
        sortedPairs.push_back(initialPairs[j]);
        used[j] = true;
        break;
      }
    }
  }

  for (size_t i = 0; i < sortedPairs.size(); ++i)
    chain.push_back(sortedPairs[i].second);

  Container order = jacobsthalOrdering<Container>(size - chain.size(), size);

  for (size_t i = 0; i < order.size(); i++) {

    size_t minVal = sortedPairs[order[i]].first;
    size_t maxVal = sortedPairs[order[i]].second;

    if (minVal != maxVal) {
      typename Container::iterator pos = std::lower_bound(chain.begin(), chain.end(), minVal, Counter());
      chain.insert(pos, minVal);
    }
  }
}

template <typename Container, typename PairContainer> PairContainer pairNumbers(Container &numbers) {
  PairContainer pairs;

  for (typename Container::iterator it = numbers.begin(); it != numbers.end();) {
    typename Container::iterator next = it;
    next++;

    if (next != numbers.end()) {
      pairs.push_back(std::make_pair(*it, *next));
      it = ++next;
    } else {
      pairs.push_back(std::make_pair(*it, *it));
      break;
    }
  }

  for (typename PairContainer::iterator it = pairs.begin(); it != pairs.end(); it++) {
    if ((*it).first > (*it).second) {
      VEC_COUNT++;
      std::swap((*it).first, (*it).second);
    }
  }
  return pairs;
}
