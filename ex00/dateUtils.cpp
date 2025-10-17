// dateUtils.cpp

// datesUtils.cpp

#include "header.hpp"

std::string findClosestEntry(const std::map<std::string, double> &data, const std::string &date) {
  if (date <= data.begin()->first)
    return data.begin()->first;

  if (date >= data.rbegin()->first)
    return data.rbegin()->first;

  std::map<std::string, double>::const_iterator it = data.lower_bound(date);

  if (it->first == date)
    return date;

  --it;

  return it->first;

  return "";
}

bool isValidDate(const std::string &date) {

  if (date.size() != 10)
    return false;

  if (date[4] != '-' || date[7] != '-')
    return false;

  for (int i = 0; i < 10; i++) {
    if (i == 7 || i == 4)
      continue;
    if (!std::isdigit(static_cast<unsigned char>(date[i])))
      return false;
  }

  int day = atoi(date.substr(8, 2).c_str());
  int month = atoi(date.substr(5, 2).c_str());
  int year = atoi(date.substr(0, 4).c_str());

  if (month > 12 || month < 1)
    return false;

  if (day > 31 || day < 1)
    return false;

  if (month == 2 && year % 4 != 0 && day > 28)
    return false;

  if (month == 2 && year % 4 == 0 && day > 29)
    return false;

  if ((month < 8 ? month % 2 == 0 : month % 2 == 1) && day > 30) {
    return false;
  }

  return true;
}
