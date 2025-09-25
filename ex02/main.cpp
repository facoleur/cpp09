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
std::vector<indexValue> getMaxima(std::vector<std::pair<indexValue, indexValue> > pairs) {
  std::vector<indexValue> result;

  for (size_t i = 0; i < pairs.size(); i++) {
    result.push_back(pairs[i].second);
  }

  return result;
}

std::vector<std::pair<indexValue, indexValue> > pairNumbers(std::vector<indexValue> &numbers) {
  std::vector<std::pair<indexValue, indexValue> > pairs;

  for (std::vector<indexValue>::iterator it = numbers.begin(); it != numbers.end();) {
    std::vector<indexValue>::iterator next = it;
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

void orientPairs(std::vector<std::pair<indexValue, indexValue> > &pairs) {
  for (std::vector<std::pair<indexValue, indexValue> >::iterator it = pairs.begin();
       it != pairs.end(); it++) {
    if ((*it).first.value > (*it).second.value) {
      indexValue temp = (*it).first;
      (*it).first = (*it).second;
      (*it).second = temp;
    }
  }
}

std::vector<std::pair<indexValue, indexValue> > addIndexes(std::vector<pair> &initialPairs) {
  std::vector<std::pair<indexValue, indexValue> > res;

  for (size_t i = 0; i < initialPairs.size(); i++) {
    indexValue a, b;
    a.index = i;
    b.index = i;
    a.value = initialPairs[i].first;
    b.value = initialPairs[i].second;
    res.push_back(std::make_pair(a, b));
  }

  return res;
}

void coutPair(std::vector<std::pair<indexValue, indexValue> > &pairs) {
  for (size_t i = 0; i < pairs.size(); ++i) {
    std::cout << "pair index: " << i << ", first.value: " << pairs[i].first.value
              << ", second.value: " << pairs[i].second.value << std::endl;
  }
}

// std::vector<indexValue> recursiveSort(std::vector<std::pair<indexValue, indexValue> > &pairs) {
//   if (pairs.size() <= 1)
//     return getMaxima(pairs);

//   std::vector<indexValue> maximas = getMaxima(pairs);
//   std::vector<std::pair<indexValue, indexValue> > maximaPairs = pairNumbers(maximas);
//   orientPairs(maximaPairs);

//   std::vector<indexValue> sortedMaxima = recursiveSort(maximaPairs);

//   std::cout << "pair size: " << pairs.size() << std::endl;
//   coutPair(pairs);

//   std::cout << std::endl;
// }

// void sort(std::vector<pair> &initialPairs) {
//   std::vector<std::pair<indexValue, indexValue> > pairs = addIndexes(initialPairs);

//   recursiveSort(pairs);
// }

indexValue makeIndexValue(size_t i, size_t v) {
  indexValue res;
  res.index = i;
  res.value = v;
  return res;
}

std::vector<indexValue> indexNumbers(std::vector<size_t> &v) {
  std::vector<indexValue> res;
  for (size_t i = 0; i < v.size(); i++) {
    res.push_back(makeIndexValue(i, v[i]));
  }
  return res;
}

int main(int ac, const char **av) {

  if (ac < 3)
    return 1;

  std::vector<size_t> numbers = parse(av);

  std::vector<indexValue> indexedNumbers = indexNumbers(numbers);

  // printVector(indexedNumbers);

  std::vector<std::pair<indexValue, indexValue> > pairs = pairNumbers(indexedNumbers);

  printPairs(pairs);

  // sort(pairs);

  return 0;
}

void sortV2(std::vector<indexValue>) {}
