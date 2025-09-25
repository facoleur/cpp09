// header.hpp

#pragma once

#include <cstdlib>
#include <iostream>
#include <utility>
#include <vector>

typedef std::vector<size_t>::iterator vec_it;

typedef std::pair<size_t, size_t> pair;
typedef std::pair<pair, pair> pair_of_pair;

typedef struct s_maxima {
  size_t index;
  size_t value;
} maxima;

template <class T> void printVector(std::vector<T> &v) {
  for (typename std::vector<T>::iterator it = v.begin(); it != v.end(); ++it) {
    std::cout << (*it).value << std::endl;
  }
}

void printPairs(std::vector<std::pair<maxima, maxima> > &pairs, const std::string &title = "print: ");
void printPairsOfPairs(const std::vector<std::pair<std::pair<size_t, size_t>, std::pair<size_t, size_t> > > &pairs,
                       const std::string &title = "pairs of pairs");

std::string removeAllWhitespace(std::string &s);
