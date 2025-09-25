// utils.cpp

#include "header.hpp"
#include <algorithm>

bool is_space(char c) { return std::isspace(static_cast<unsigned char>(c)) != 0; }

std::string removeAllWhitespace(std::string &s) {
  s.erase(std::remove_if(s.begin(), s.end(), is_space), s.end());
  return s;
}

void printPairs(std::vector<std::pair<indexValue, indexValue> > &pairs, const std::string &title) {
  std::cout << title << std::endl;

  for (std::vector<std::pair<indexValue, indexValue> >::iterator it = pairs.begin();
       it != pairs.end(); ++it) {
    std::cout << "(" << "[" << (*it).first.index << "]" << (*it).first.value << ", " << "["
              << (*it).second.index << "]" << (*it).second.value << ") ";
  }
  std::cout << std::endl;
}

void printPairsOfPairs(
    const std::vector<std::pair<std::pair<size_t, size_t>, std::pair<size_t, size_t> > > &pairs,
    const std::string &title) {
  std::cout << title << std::endl;
  for (std::vector<
           std::pair<std::pair<size_t, size_t>, std::pair<size_t, size_t> > >::const_iterator it =
           pairs.begin();
       it != pairs.end(); ++it) {
    std::cout << "((" << it->first.first << ", " << it->first.second << "), (" << it->second.first
              << ", " << it->second.second << ")) ";
  }
  std::cout << std::endl;
}

void printVector(std::vector<indexValue> &v) {
  for (std::vector<indexValue>::iterator it = v.begin(); it != v.end(); ++it) {
    std::cout << "[" << (*it).index << "]: " << (*it).value << std::endl;
  }
  std::cout << std::endl;
}

void printVector(std::vector<size_t> &v) {
  for (std::vector<size_t>::iterator it = v.begin(); it != v.end(); ++it) {
    std::cout << (*it) << std::endl;
  }
}
