// main.cpp

#include "header.hpp"

std::map<std::string, double> parseData(std::ifstream &datafile) {
  std::string line;

  std::map<std::string, double> data;

  std::getline(datafile, line);

  while (std::getline(datafile, line)) {
    int comma = line.find(',');

    std::string date = line.substr(0, comma);

    if (!isValidDate(date)) {
      throw std::runtime_error("data: unvalid date");
    }

    std::string price = line.substr(comma + 1);

    char *endp = 0;
    data[date] = strtod(price.c_str(), &endp);

    if (price.c_str() == endp)
      throw std::runtime_error("data: unvalid price");
  }

  if (data.empty())
    throw std::runtime_error("data: no data");

  return data;
}

struct s_line {
  std::string date;
  double units;
};

s_line parseLine(std::string &line) {
  line = remove_all_whitespace(line);
  size_t separator = line.find('|');

  if (separator == std::string::npos)
    throw std::runtime_error("bad input: " + line);

  std::string date = line.substr(0, separator);

  std::string priceStr = line.substr(separator + 1);

  char *endp;
  double units = strtod(priceStr.c_str(), &endp);

  if (endp == priceStr.c_str())
    throw std::runtime_error("must provide a value");

  if (units > 1000)
    throw std::runtime_error("too large number");

  if (units < 0)
    throw std::runtime_error("not a positive number");

  if (!isValidDate(date))
    throw std::runtime_error("not valid date");

  s_line res;

  res.date = date;
  res.units = units;

  return res;
}

void compute(std::ifstream &inputfile, std::map<std::string, double> &data) {
  std::string line;
  (void)data;
  std::map<std::string, double> input;

  std::string header;
  std::getline(inputfile, header);

  if (header.find("date") == std::string::npos ||
      header.find("value") == std::string::npos) {
    throw std::runtime_error("Error: header is not valid.");
  }

  while (std::getline(inputfile, line)) {
    if (!line[0])
      continue;

    try {
      s_line parsedLine = parseLine(line);

      const std::string closestDate = findClosestEntry(data, parsedLine.date);
      const double price = data[closestDate];

      std::cout << closestDate << " => " << price << " = "
                << price * parsedLine.units << std::endl;

    } catch (std::exception &e) {
      std::cout << e.what() << std::endl;
    }
  }
}

int main(int ac, char **av) {

  if (ac != 2 || isDirectory(av[1]) || !canOpenFile(av[1], "r")) {
    std::cout << "Error: could not open file." << std::endl;
    return 1;
  }

  std::ifstream inputfile(av[1]);
  std::ifstream datafile("data.csv");

  try {
    std::map<std::string, double> data = parseData(datafile);
    compute(inputfile, data);

  } catch (std::exception &e) {
    std::cout << e.what() << std::endl;
  }

  return 0;
}
