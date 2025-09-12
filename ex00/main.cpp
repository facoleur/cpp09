// main.cpp

#include "header.hpp"

std::map<std::string, double> parseData(std::ifstream &datafile) {
  std::string line;

  std::map<std::string, double> data;

  while (std::getline(datafile, line)) {
    int comma = line.find(',');

    std::string date = line.substr(0, comma);
    std::string price = line.substr(comma + 1);

    data[date] = strtod(price.c_str(), NULL);

    // std::cout << date << ": " << data[date] << std::endl;
  }

  return data;
}

std::string getDayBefore(const std::string &date) {

  int day = atoi(date.substr(8, 2).c_str());
  int month = atoi(date.substr(5, 2).c_str());
  int year = atoi(date.substr(0, 4).c_str());

  if (day > 1) {
    day--;
  } else if (month > 1) {
    month--;
    if (month == 2) {
      if (year % 4 == 0)
        day = 29;
      else
        day = 28;
    } else {
      if (month < 8) {
        if (month % 2 == 0) {
          day = 30;
        } else {
          day = 31;
        }
      } else {
        if (month % 2 == 0) {
          day = 31;
        } else {
          day = 30;
        }
      }
    }
  } else {
    year--;
    day = 31;
    month = 12;
  }

  std::string dayStr;
  std::string monthStr;
  std::string yearStr;

  if (day > 9) {
    dayStr = itoa(day);
  } else {
    dayStr = "0" + itoa(day);
  }
  if (month > 9) {
    monthStr = itoa(month);
  } else {
    monthStr = "0" + itoa(month);
  }
  yearStr = itoa(year);

  std::string newDate = yearStr + "-" + monthStr + "-" + dayStr;
  std::cout << newDate << std::endl;

  return newDate;
}

std::string findClosestDate(std::string &date,
                            std::map<std::string, double> &data) {

  std::string foundDate = "0";

  while (1) {
    for (std::map<std::string, double>::iterator it = data.begin();
         it != data.end(); it++) {
      if (it->first == date) {
        foundDate = date;
        std::cout << foundDate << std::endl;
        return foundDate;
        break;
        // date = getDayBefore(date);
      }
    }

    if (foundDate != "0") {
      std::cout << foundDate << std::endl;
      return foundDate;
    }
    date = getDayBefore(date);
  }
}

void manageInput(std::ifstream &inputfile,
                 std::map<std::string, double> &data) {
  std::string line;
  (void)data;
  std::map<std::string, double> input;

  std::string header;
  std::getline(inputfile, header);

  if (header.find("date") == std::string::npos ||
      header.find("value") == std::string::npos) {
    throw;
  }

  while (std::getline(inputfile, line)) {

    if (!line[0])
      continue;

    size_t separator = line.find('|');
    line = remove_all_whitespace(line);

    if (separator == std::string::npos)
      throw std::runtime_error("bad input: " + line);

    std::string date = line.substr(0, separator - 1);

    std::string priceStr = line.substr(separator);

    char *endp;
    double units = strtod(priceStr.c_str(), &endp);

    if (endp == priceStr)
      throw std::runtime_error("must provide a value");

    if (units > INT_MAX)
      throw std::runtime_error("too large number");

    if (units < 0)
      throw std::runtime_error("not a positive number");

    findClosestDate

    // std::cout << date << std::endl;
    // double value = data[findClosestDate(date, data)] * units;
    // std::cout << value << std::endl;
  }
}

int main() {

  std::ifstream datafile("data.csv");
  std::ifstream inputfile("input.txt");
  std::map<std::string, double> data = parseData(datafile);

  manageInput(inputfile, data);

  return 0;
}
