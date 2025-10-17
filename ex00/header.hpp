// header.hpp

#include <algorithm>
#include <cctype>
#include <climits>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <sys/stat.h>

bool is_space(char c);
std::string removeAllWhitespace(std::string &s);
std::string itoa(int value);
bool canOpenFile(const char *path, const char *mode);
bool isDirectory(const char *path);

bool isValidDate(const std::string &date);

std::string findClosestEntry(const std::map<std::string, double> &data, const std::string &date);
