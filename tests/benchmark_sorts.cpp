// (c) Copyright 2015 Josh Wright

#include <debug.h>
#include <iomanip>
#include <chrono>
#include "quicksort.h"
#include "mergesort.h"

int main(int argc, char const *argv[]) {
  using std::vector;
  using namespace containers;
  using namespace std::chrono;

  srand(time(nullptr));

  const size_t wid = 15; /*each column is the same width*/
  /*write the header*/
  std::cout << std::setw(wid) << "size";
  std::cout << std::setw(wid) << "stdlib";
  std::cout << std::setw(wid) << "quick";
  std::cout << std::setw(wid) << "merge";
  std::cout << std::setw(wid) << "std/quick";
  std::cout << std::setw(wid) << "std/merge";
  std::cout << std::setw(wid) << "quick/merge";
  std::cout << std::setw(wid) << "merge/quick";
  std::cout << std::endl;
  const size_t testsize = (1 << 21);

  for (size_t sz = 64; sz < testsize; sz *= 2) {
    for (int i = 0; i < 4; i++) {

      /*make a vector of random strings*/
      vector <std::string> unsorted(testsize);
      size_t len = 20;
      std::generate(unsorted.begin(), unsorted.end(), [len]() {
        static const char alphanum[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
        std::string out(len, 'a');
        std::generate(out.begin(), out.end(), [alphanum]() {
          return alphanum[rand() % (sizeof(alphanum) - 1)];
        });
        return out;
      });
      /*get the same unsorted list*/
      vector <std::string> sorted_stdlib = unsorted;
      vector <std::string> sorted_quick = unsorted;
      vector <std::string> sorted_merge = unsorted;


      /*sort the lists, timing each*/
      high_resolution_clock::time_point start = high_resolution_clock::now();
      std::sort(sorted_stdlib.begin(), sorted_stdlib.end(),
                std::less<std::string>());
      high_resolution_clock::time_point mid1 = high_resolution_clock::now();
      mergesort(sorted_merge.begin(), sorted_merge.end(),
                std::less<std::string>(), sz);
      high_resolution_clock::time_point mid2 = high_resolution_clock::now();
      quicksort(sorted_quick.begin(), sorted_quick.end(),
                std::less<std::string>(), sz);
      high_resolution_clock::time_point end = high_resolution_clock::now();

      test(sorted_stdlib == sorted_quick, "quick sort");
      test(sorted_stdlib == sorted_merge, "merge sort");

      /*calculate the time used by each sorting algorithm*/
      auto time_stdlib = (mid1 - start).count();
      auto time_quicksort = (mid2 - mid1).count();
      auto time_merge = (end - mid1).count();

      /*output timing data*/
      std::cout << std::setw(wid) << sz;
      std::cout << std::setw(wid) << time_stdlib;
      std::cout << std::setw(wid) << time_quicksort;
      std::cout << std::setw(wid) << time_merge;
      std::cout << std::setw(wid) << 1.0 * time_stdlib / time_quicksort;
      std::cout << std::setw(wid) << 1.0 * time_stdlib / time_merge;
      std::cout << std::setw(wid) << 1.0 * time_quicksort / time_merge;
      std::cout << std::setw(wid) << 1.0 * time_merge / time_quicksort;
      std::cout << std::endl;

    }
  }

  return 0;
}
