// (c) Copyright 2015 Josh Wright
#pragma once

#include <algorithm>

namespace containers {

  template<typename RAIter, class Compare = std::less<typename RAIter::value_type>>
  void quicksort(const RAIter first, const RAIter last,
                 const Compare comp = Compare(), const size_t threshold = 32) {
    typedef typename RAIter::value_type value_type;
    using std::swap;

    const size_t datasize = last - first;

    if (datasize < threshold) {
      /*don't bother recursing on small lists*/
      std::sort(first, last, comp);
    } else {
      value_type pivot = first[rand() % datasize]; /*random pivot*/

      auto r = first, l = last - 1;
      while (true) {
        /*advance iterators if their element is correctly placed*/
        while (comp(*r, pivot)) {
          ++r;
        }
        while (comp(pivot, *l)) {
          --l;
        }

        if (l > r) {
          /*swap values because the iterators are now *both* pointing to values
           * in the wrong place*/
          swap(*r, *l);
          ++r;
          --l;
        } else {
          /*iteratos have crossed*/
          break;
        }
      }
#pragma omp parallel sections
      {
#pragma omp section
        if (r < last) quicksort(r, last, comp, threshold);
#pragma omp section
        if (l > first) quicksort(first, l + 1, comp, threshold);
      }
      return;
    }
  };

}