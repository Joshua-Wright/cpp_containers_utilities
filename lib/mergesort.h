// (c) Copyright 2015 Josh Wright
#pragma once

#include <algorithm>

namespace containers {

  template<typename RAIter, class Compare = std::less<typename RAIter::value_type>>
  void mergesort(const RAIter first, const RAIter last,
                 const Compare comp = Compare(), const size_t threshold = 32) {
    using std::swap;
    using std::inplace_merge;

    size_t range = last - first;

    if (range < threshold) {
      /*don't bother recursing on small lists*/
      std::sort(first, last, comp);
    } else {
      /*split and merge*/
      const size_t mid = range / 2;

#pragma omp parallel sections
      { /*sort the sub-lists in-place*/
#pragma omp section
        mergesort(first, first + mid, comp, threshold);
#pragma omp section
        mergesort(first + mid, last, comp, threshold);
      }
      inplace_merge(first, first + mid, last, comp);

    }
  };
}

