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
  }
}

template <typename Container> void sort_pairs(Container &vect) {
  for (size_t i = 0; i < vect.size() - 1; i += 2) {
    if (vect[i] > vect[i + 1])
      std::swap(vect[i], vect[i + 1]);
  }
}

template <typename Container> Container get_minima(const Container &vect) {
  Container minima;
  for (size_t i = 0; i + 1 < vect.size(); i += 2)
    minima.push_back(vect[i]);
  if (vect.size() % 2 != 0)
    minima.push_back(vect.back());
  return minima;
}

template <typename Container> Container get_maxima(const Container &vect) {
  Container maxima;
  for (size_t i = 1; i < vect.size(); i += 2)
    maxima.push_back(vect[i]);
  return maxima;
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

template <typename Container> Container get_order(size_t n, size_t size) {
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

template <typename Container> void print_container(Container &v, const std::string &title) {
  if (!title.empty())
    std::cout << title;

  for (typename Container::iterator it = v.begin(); it != v.end(); ++it)
    std::cout << (*it) << " ";

  std::cout << std::endl;
}

template <typename Container> Container sort(Container &vect) {
  Container maxima = get_maxima<Container>(vect);
  Container sortedMaximas = recursive_maxima_sort(maxima);

  Container minima = get_minima<Container>(vect);

  Container chain;

  chain.insert(minima[0]);

  Container order = get_order(maxima, vect);

  for (size_t i = 0; i < maxima.size(); ++i) {
    size_t index = order[i];
    typename Container::iterator it = std::lower_bound(chain.begin(), chain.end(), maxima[index]);
    chain.insert(it, maxima[index]);
  }
}

template <typename Container> Container recursive_maxima_sort(Container &vect) {
  sort_pairs(vect);
  if (vect.size() <= 2)
    return vect;

  Container minima = get_minima<Container>(vect);
  Container maxima = get_maxima<Container>(vect);

  Container sorted = recursive_maxima_sort(maxima);

  for (size_t i = 0; i < minima.size(); ++i) {
    typename Container::iterator it = std::lower_bound(sorted.begin(), sorted.end(), minima[i]);
    sorted.insert(it, minima[i]);
  }

  return sorted;
}
