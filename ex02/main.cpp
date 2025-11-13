// main.cpp

#include "header.hpp"

size_t VEC_COUNT = 0;

std::vector<size_t> recursive_maxima_sort(std::vector<size_t> &vect);

int main(int ac, const char **av) {

  (void)ac;
  (void)av;

  if (ac < 2`) {
    std::cout << "Usage: " << av[0] << " <list of positive integers>" << std::endl;
    return 1;
  }

  int vecStart = clock();
  std::vector<size_t> vec;
  std::vector<size_t> vecSorted;
  try {
    parse<std::vector<size_t> >(av, vec);
    vecSorted = recursive_maxima_sort<std::vector<size_t> >(vec);
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
    deqSorted = recursive_maxima_sort<std::deque<size_t> >(deq);
  } catch (std::exception &e) {
    std::cout << e.what() << std::endl;
    return 1;
  }

  int deqEnd = clock();
  double deqDurationSeconds = double(deqEnd - deqStart) / CLOCKS_PER_SEC;

  print_vector(vec, "before: ");
  print_vector(vecSorted, "after:  ");

  std::cout << "time to process a range of " << vec.size() << " elements with std::vector : " << std::setprecision(10) << vecDurationSeconds << "s"
            << std::endl;

  std::cout << "time to process a range of " << deq.size() << " elements with std::deque : " << std::setprecision(10) << deqDurationSeconds << "s" << std::endl;

  return 0;
}
