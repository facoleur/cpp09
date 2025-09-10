#include "header.hpp"

bool is_space(char c) {
  return std::isspace(static_cast<unsigned char>(c)) != 0;
}

std::string remove_all_whitespace(std::string &s) {
  s.erase(std::remove_if(s.begin(), s.end(), is_space), s.end());
  return s;
}

std::string itoa(int value) {
  std::ostringstream oss;
  oss << value;
  return oss.str();
}
