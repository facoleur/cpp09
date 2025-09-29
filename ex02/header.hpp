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
#include <utility>
#include <vector>

extern size_t VEC_COUNT;

struct CountingLess {
  bool operator()(const size_t &a, const size_t &b) const {
    VEC_COUNT++;
    return a < b;
  }
};

// utils
double factorial(double n);
int min_comparisons_bound(double n);
int avg_comparisons_bound(unsigned int n);

void printPairs(std::vector<std::pair<size_t, size_t> > &, const std::string &title = "");
void printVector(std::vector<std::pair<size_t, size_t> > &v);
void printVector(std::vector<size_t> &, const std::string & = "");

// algo templates
template <typename Container> void parse(const char **, Container &);
template <typename Container, typename PairContainer> PairContainer pairNumbers(Container &numbers);
template <typename Container> Container jacobsthal(size_t);
template <typename Container> Container jacobsthalOrdering(size_t, size_t);
template <typename Container> Container fordJohnsonSortMaxima(const Container &);
template <typename Container, typename PairContainer> void sort(PairContainer &, Container &, size_t);

#include "algo.tpp"
