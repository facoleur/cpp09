// main.cpp

#include "header.hpp"

size_t VEC_COUNT = 0;

int main(int ac, const char **av) {

  if (ac < 3) {
    std::cout << "Usage: " << av[0] << " <list of positive integers>" << std::endl;
    return 1;
  }

  int vecStart = clock();
  std::vector<size_t> vec;
  std::vector<size_t> vecSorted;
  try {
    parse<std::vector<size_t> >(av, vec);
    std::vector<std::pair<size_t, size_t> > vecPair = pairNumbers<std::vector<size_t>, std::vector<std::pair<size_t, size_t> > >(vec);
    sort<std::vector<bool>, std::vector<size_t>, std::vector<std::pair<size_t, size_t> > >(vecPair, vecSorted, vec.size());
  } catch (std::exception &e) {
    std::cout << e.what() << std::endl;
    return 1;
  }
  int vecEnd = clock();
  double vecDurationSeconds = double(vecEnd - vecStart) / CLOCKS_PER_SEC;

  int deqStart = clock();
  std::deque<size_t> deq;
  std::deque<size_t> deqSorted;
  try {
    parse<std::deque<size_t> >(av, deq);
    std::deque<std::pair<size_t, size_t> > deqPair = pairNumbers<std::deque<size_t>, std::deque<std::pair<size_t, size_t> > >(deq);
    sort<std::deque<bool>, std::deque<size_t>, std::deque<std::pair<size_t, size_t> > >(deqPair, deqSorted, deq.size());
  } catch (std::exception &e) {
    std::cout << e.what() << std::endl;
    return 1;
  }

  int deqEnd = clock();
  double deqDurationSeconds = double(deqEnd - deqStart) / CLOCKS_PER_SEC;

  printVector(vec, "before: ");
  printVector(vecSorted, "after:  ");

  std::cout << "time to process a range of " << vec.size() << " elements with std::vector : " << std::setprecision(10) << vecDurationSeconds << "s"
            << std::endl;

  std::cout << "time to process a range of " << deq.size() << " elements with std::deque : " << std::setprecision(10) << deqDurationSeconds << "s" << std::endl;

  return 0;
}
