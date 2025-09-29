// utils.cpp

#include "header.hpp"
#include <algorithm>

void printPairs(std::vector<std::pair<size_t, size_t> > &pairs, const std::string &title) {
  std::cout << title << std::endl;

  for (std::vector<std::pair<size_t, size_t> >::iterator it = pairs.begin(); it != pairs.end(); ++it) {
    std::cout << "(" << (*it).first << ", " << (*it).second << ") ";
  }
  std::cout << std::endl;
}

void printVector(std::vector<std::pair<size_t, size_t> > &v) {
  for (std::vector<std::pair<size_t, size_t> >::iterator it = v.begin(); it != v.end(); ++it) {
    std::cout << "(" << (*it).first << ", " << (*it).second << ")" << std::endl;
  }
  std::cout << std::endl;
}

void printVector(std::vector<size_t> &v, const std::string &title) {
  if (!title.empty())
    std::cout << title;

  for (std::vector<size_t>::iterator it = v.begin(); it != v.end(); ++it)
    std::cout << (*it) << " ";

  std::cout << std::endl;
}

double factorial(double n) {
  if (n <= 1)
    return 1;
  return n * factorial(n - 1);
}

int min_comparisons_bound(double n) { return static_cast<size_t>(std::ceil(std::log(factorial(n)) / log(2))); }

int avg_comparisons_bound(unsigned int n) { return n * log2(n); }
