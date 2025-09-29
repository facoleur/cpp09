// algo.tpp

#include "header.hpp"

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

  for (size_t i = size % 2; i < j.size(); i++)
    indices.push_back(j[i]);

  for (size_t i = 0; i <= n; i++) {
    if (std::find(j.begin(), j.end(), i) == j.end()) {
      indices.push_back(i);
    }
  }

  return indices;
}

template <typename Container> Container fordJohnsonSortMaxima(const Container &maxima) {
  Container chain;

  if (maxima.empty())
    return chain;

  chain.push_back(maxima[0]);

  size_t blockSize = 1;
  while (blockSize < maxima.size()) {
    size_t start = blockSize;
    size_t end = std::min(blockSize * 2, maxima.size());

    for (size_t i = start; i < end; ++i) {
      typename Container::iterator pos = std::lower_bound(chain.begin(), chain.end(), maxima[i], CountingLess());
      chain.insert(pos, maxima[i]);
    }

    blockSize *= 2;
  }

  return chain;
}

template <typename Container, typename PairContainer>
void sort(PairContainer &initialPairs, Container &chain, size_t size) {

  if (initialPairs.size() <= 1) {
    chain.push_back(initialPairs[0].first);
    chain.push_back(initialPairs[0].second);
    return;
  }

  Container maxima;
  for (size_t i = 0; i < initialPairs.size(); ++i)
    maxima.push_back(initialPairs[i].second);

  Container sortedMaxima = fordJohnsonSortMaxima(maxima);

  PairContainer sortedPairs;
  std::vector<bool> used(initialPairs.size(), false);

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

  for (size_t i = 0; i < sortedPairs.size(); i++) {
    size_t minVal = sortedPairs[i].first;
    size_t maxVal = sortedPairs[i].second;

    if (minVal != maxVal) {
      typename Container::iterator pos = std::lower_bound(chain.begin(), chain.end(), minVal, CountingLess());
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
      size_t temp = (*it).first;
      (*it).first = (*it).second;
      (*it).second = temp;
    }
  }
  return pairs;
}
