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
} indexValue;

void printPairs(std::vector<std::pair<indexValue, indexValue> > &pairs,
                const std::string &title = "print: ");
void printVector(std::vector<indexValue> &v);
void printVector(std::vector<size_t> &v);

std::string removeAllWhitespace(std::string &s);
