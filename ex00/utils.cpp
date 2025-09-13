// utils.cpp

#include "header.hpp"

bool is_space(char c) {
  return std::isspace(static_cast<unsigned char>(c)) != 0;
}

std::string removeAllWhitespace(std::string &s) {
  s.erase(std::remove_if(s.begin(), s.end(), is_space), s.end());
  return s;
}

std::string itoa(int value) {
  std::ostringstream oss;
  oss << value;
  return oss.str();
}

bool isDirectory(const char *path) {
  struct stat info;
  if (stat(path, &info) != 0) {
    return false;
  }
  return (info.st_mode & S_IFMT) == S_IFDIR;
}

bool canOpenFile(const char *path, const char *mode) {
  FILE *f = fopen(path, mode);
  if (f == NULL) {
    return false;
  }
  fclose(f);
  return true;
}
