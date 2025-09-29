// main.cpp

#include "header.hpp"

size_t VEC_COUNT = 0;

int main(int ac, const char **av) {

  if (ac < 2) {
    std::cout << "Usage: " << av[0] << " <list of positive integers>" << std::endl;
    return 1;
  }

  int vecStart = clock();
  std::vector<size_t> vec;
  parse<std::vector<size_t> >(av, vec);
  std::vector<std::pair<size_t, size_t> > vecPair =
      pairNumbers<std::vector<size_t>, std::vector<std::pair<size_t, size_t> > >(vec);

  std::vector<size_t> vecSorted;
  sort<std::vector<size_t>, std::vector<std::pair<size_t, size_t> > >(vecPair, vecSorted, vec.size());
  int vecEnd = clock(); 
  double vecDurationSeconds = double(vecEnd - vecStart) / CLOCKS_PER_SEC;

  int deqStart = clock();
  std::deque<size_t> deq;
  parse<std::deque<size_t> >(av, deq);
  std::deque<std::pair<size_t, size_t> > deqPair =
      pairNumbers<std::deque<size_t>, std::deque<std::pair<size_t, size_t> > >(deq);
  std::deque<size_t> deqSorted;
  sort<std::deque<size_t>, std::deque<std::pair<size_t, size_t> > >(deqPair, deqSorted, deq.size());

  int deqEnd = clock();
  double deqDurationSeconds = double(deqEnd - deqStart) / CLOCKS_PER_SEC;

  int min_case_comparison = min_comparisons_bound(static_cast<double>(vec.size()));
  int avg_case_comparison = avg_comparisons_bound(vec.size());

  printVector(vec, "before: ");
  printVector(vecSorted, "after:  ");

  std::cout << "time to process a range of " << vec.size() << " elements with std::vector : " << std::setprecision(10)
            << vecDurationSeconds << "s" << std::endl;

  std::cout << "time to process a range of " << deq.size() << " elements with std::deque : " << std::setprecision(10)
            << deqDurationSeconds << "s" << std::endl;

  std::cout << std::endl;
  // divided by 2 because its counted in vector AND deque, so the count is actually 2x bigger than reality
  std::cout << "Vectors comparison count:    " << VEC_COUNT / 2 << std::endl;
  std::cout << "Vectors minimum comparisons: " << min_case_comparison << std::endl;
  std::cout << "Vectors average comparisons: " << avg_case_comparison << std::endl;

  return 0;
}
