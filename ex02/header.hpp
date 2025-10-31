// header.hpp

#pragma once

#include <algorithm>
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <ctime>
#include <deque>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <utility>
#include <vector>

extern size_t VEC_COUNT;

struct Counter {
  bool operator()(const size_t &a, const size_t &b) const {
    VEC_COUNT++;
    return a < b;
  }
};

// utils
void print_pairs(std::vector<std::pair<size_t, size_t> > &, const std::string &title = "");
void print_vector(std::vector<std::pair<size_t, size_t> > &v);
void print_vector(std::vector<size_t> &, const std::string & = "");

// algo templates
template <typename Container> void parse(const char **, Container &);
template <typename Container> Container jacobsthal(size_t);
template <typename Container> Container get_order(size_t, size_t);
template <typename Container> Container recursive_maxima_sort(Container &);

#include "algo.tpp"
