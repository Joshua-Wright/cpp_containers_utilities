// (c) Copyright 2015 Josh Wright
#pragma once

#include <algorithm>

namespace containers {

  template<typename RAIter, class Compare = std::less<typename RAIter::value_type>>
  void mergesort(RAIter first, RAIter last, Compare comp = Compare()) {
    using std::swap;
    using std::inplace_merge;

    size_t range = last - first;
    if (range <= 1) {
      /*single element is sorted*/
      return;
    } else if (range == 2) {
      /*trivial 2-element case*/
      if (comp(*(first + 1), *first)) {
        swap(*(first + 1), *first);
      }
    } else {
      /*split and merge*/
      const size_t mid = range / 2;
      { /*sort the sub-lists in-place*/
#pragma omp task
        mergesort(first, first + mid, comp);

#pragma omp task
        mergesort(first + mid, last, comp);

#pragma omp taskwait
        inplace_merge(first, first + mid, last, comp);
      }
    }
  };
}

