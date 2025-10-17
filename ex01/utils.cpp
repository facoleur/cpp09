// utils.cpp

#include "header.hpp"
#include <algorithm>

bool is_space(char c) { return std::isspace(static_cast<unsigned char>(c)) != 0; }

std::string removeAllWhitespace(std::string &s) {
  s.erase(std::remove_if(s.begin(), s.end(), is_space), s.end());
  return s;
}
