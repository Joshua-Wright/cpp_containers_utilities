// (c) Copyright 2015 Josh Wright

#include <debug.h>
#include "mergesort.h"

int main(int argc, char const *argv[]) {
  using std::vector;
  using namespace containers;
  vector<unsigned long> unsorted(1024*1024*10);
  std::generate(unsorted.begin(), unsorted.end(), rand);

  vector<unsigned long> sorted_stdlib = unsorted;
  vector<unsigned long> sorted_containers = unsorted;

  std::sort(sorted_stdlib.begin(), sorted_stdlib.end());
  mergesort(sorted_containers.begin(), sorted_containers.end());

  test(sorted_containers == sorted_stdlib, "sort");


//  std::cout << "stdlib:" << std::endl;
//  for (auto &x : sorted_stdlib) {
//    std::cout << x << std::endl;
//  }
//  std::cout << "containers:" << std::endl;
//  for (auto &x : sorted_containers) {
//    std::cout << x << std::endl;
//  }

  return 0;
}
