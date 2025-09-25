// main.cpp

#include "header.hpp"

void jacobsthal() {
  size_t a = 0;
  size_t b = 1;

  std::vector<size_t> jacobsthal;

  jacobsthal.push_back(0);
  jacobsthal.push_back(1);

  size_t n;
  for (size_t i = 2; i < 30; i++) {
    n = b + 2 * a;
    jacobsthal.push_back(n);
    a = b;
    b = n;
  }
}

std::vector<size_t> parse(const char **input) {
  std::vector<size_t> numbers;
  for (int i = 1; input[i]; i++) {
    if (atoi(input[i]) == 0 && input[i] - '0' != 0)
      throw std::runtime_error("invalid input");
    numbers.push_back(atoi(input[i]));
  }
  return numbers;
}

// returns [(index, value)]
std::vector<pair> getMaximaWithIndex(std::vector<pair> pairs) {
  std::vector<pair> result;

  for (size_t i = 0; i < pairs.size(); i++) {
    result.push_back(std::make_pair(i, pairs[i].second)); // i = index of pair
  }

  return result;
}

// returns [value]
std::vector<maxima> getMaxima(std::vector<std::pair<maxima, maxima> > pairs) {
  std::vector<maxima> result;

  for (size_t i = 0; i < pairs.size(); i++) {
    result.push_back(pairs[i].second);
  }

  return result;
}

std::vector<std::pair<maxima, maxima> > pairNumbers(std::vector<maxima> &numbers) {
  std::vector<std::pair<maxima, maxima> > pairs;

  for (std::vector<maxima>::iterator it = numbers.begin(); it != numbers.end();) {
    std::vector<maxima>::iterator next = it;
    next++;

    if (next != numbers.end()) {
      pairs.push_back(std::make_pair(*it, *next));
      it = ++next;
    } else {
      pairs.push_back(std::make_pair(*it, *it));
      break;
    }
  }

  return pairs;
}

std::vector<std::pair<size_t, size_t> > pairNumbers(std::vector<size_t> &numbers) {
  std::vector<std::pair<size_t, size_t> > pairs;

  for (std::vector<size_t>::iterator it = numbers.begin(); it != numbers.end();) {
    std::vector<size_t>::iterator next = it;
    next++;

    if (next != numbers.end()) {
      pairs.push_back(std::make_pair(*it, *next));
      it = ++next;
    } else {
      pairs.push_back(std::make_pair(*it, *it));
      break;
    }
  }

  return pairs;
}

void orientPairs(std::vector<std::pair<maxima, maxima> > &pairs) {
  for (std::vector<std::pair<maxima, maxima> >::iterator it = pairs.begin(); it != pairs.end(); it++) {
    if ((*it).first.value > (*it).second.value) {
      maxima temp = (*it).first;
      (*it).first = (*it).second;
      (*it).second = temp;
    }
  }
}

std::vector<std::pair<maxima, maxima> > addIndexes(std::vector<pair> &initialPairs) {
  std::vector<std::pair<maxima, maxima> > res;

  for (size_t i = 0; i < initialPairs.size(); i++) {
    maxima a, b;
    a.index = i;
    b.index = i;
    a.value = initialPairs[i].first;
    b.value = initialPairs[i].second;
    res.push_back(std::make_pair(a, b));
  }

  return res;
}

void sort(std::vector<pair> &initialPairs) {
  if (initialPairs.size() <= 1)
    return;

  std::vector<std::pair<maxima, maxima> > pairs = addIndexes(initialPairs);
  std::vector<maxima> sortedMaxima;

  while (pairs.size() > 1) {
    std::vector<maxima> maximas = getMaxima(pairs);

    for (std::vector<maxima>::iterator it = maximas.begin(); it != maximas.end(); ++it) {
      sortedMaxima.push_back(*it);
    }

    std::vector<std::pair<maxima, maxima> > maximaPairs = pairNumbers(maximas);
    orientPairs(maximaPairs);

    pairs = maximaPairs;
  }

  sortedMaxima.push_back(pairs[0].first);
  if (pairs[0].second.index != pairs[0].first.index)
    sortedMaxima.push_back(pairs[0].second);

  printVector(sortedMaxima);
}

// std::vector<pair> recursiveSort(std::vector<pair> &pairs) {

//   if (pairs.size() <= 1)
//     return;

//   std::vector<pair> maxima = getMaximaWithIndex(pairs);

//   std::vector<size_t> maximaValues;
//   for (size_t i = 0; i < maxima.size(); ++i) {
//     maximaValues.push_back(maxima[i].second);
//   }

//   std::vector<pair_of_pair> maximaPairs = pairNumbersWithIndex(maxima);

//   sortPairsOfPairs(maximaPairs);

//   std::vector<pair> sortedMaxima;
//   for (size_t i = 0; i < maximaPairs.size(); i++) {
//     sortedMaxima.push_back(maximaPairs[i].second);
//   }

//   std::vector<pair> newpair recursiveSort(sortedMaxima);

//   std::vector<pair> sorted;
//   std::vector<bool> used(pairs.size(), false);

//   for (size_t k = 0; k < sortedMaxima.size(); ++k) {
//     size_t idx = sortedMaxima[k].first;
//     if (!used[idx]) {
//       sorted.push_back(pairs[idx]);
//       used[idx] = true;
//     }
//   }

//   pairs.swap(sorted);
// }

int main(int ac, const char **av) {

  if (ac < 3)
    return 1;

  std::vector<size_t> numbers = parse(av);
  std::vector<pair> pairs = pairNumbers(numbers);

  sort(pairs);

  // std::vector<size_t> bigs = getMaximaWithIndex(pairs);
  // printVector<size_t>(bigs);

  jacobsthal();
  return 0;
}
