// (c) Copyright 2016 Josh Wright
#include "testing.h"
#include "util/debug.h"
#include "util/matrix.h"
#include <cassert>
#include <iomanip>
#include <iostream>
#include <cstdlib>

template <class T>
struct Mallocator {
  typedef T value_type;
  Mallocator() = default;
  template <class U>
  Mallocator(const Mallocator<U> &) {}
  T *allocate(std::size_t n) { return static_cast<T *>(std::malloc(n * sizeof(T))); }
  void deallocate(T *p, std::size_t) { std::free(p); }
};
template <class T, class U>
bool operator==(const Mallocator<T>&, const Mallocator<U>&) { return true; }
template <class T, class U>
bool operator!=(const Mallocator<T>&, const Mallocator<U>&) { return false; }


int main() {
  using util::matrix;
  {
    matrix<int> test_matrix(5, 5);
    test_matrix(1) = 7;
    test_matrix(20) = 18;
    test_matrix(4, 4) = 23;
    test_matrix(3, 4) = 14;

    assert(test_matrix(1) == 7);
    assert(test_matrix(20) == 18);
    assert(test_matrix(4, 4) == 23);
    assert(test_matrix(3, 4) == 14);
    assert(test_matrix(2) == 0);
    assert(test_matrix(2, 2) == 0);
  }
  {
    /*test matrix element operations*/
    long x = 20;
    long y = 20;
    /*test array element-wise operations*/
    matrix<long> test_array_1(x, y, 0);
    matrix<long> test_array_2(x, y, 0);
    matrix<long> test_array_3(x, y, 0);
    matrix<long> test_array_4(x, y, 0);
    matrix<long> test_array_5(x, y, 0);
    for (long i = 0; i < x; i++) {
      for (long j = 0; j < y; j++) {
        test_array_1(i, j) = i * j - i;
        test_array_2(i, j) = i * j - i;
        test_array_3(i, j) = i * j - i;
        test_array_4(i, j) = i * j - i;
        test_array_5(i, j) = i * j - i;
      }
    }
    test_array_1 *= 4;
    test_array_2 /= 4;
    test_array_3 += 4;
    test_array_4 -= 4;
    test_array_5 %= 4;

    for (long i = 0; i < x; i++) {
      for (long j = 0; j < y; j++) {
        assert(test_array_1(i, j) == (i * j - i) * 4);
        assert(test_array_2(i, j) == (i * j - i) / 4);
        assert(test_array_3(i, j) == (i * j - i) + 4);
        assert(test_array_4(i, j) == (i * j - i) - 4);
        assert(test_array_5(i, j) == (i * j - i) % 4);
      }
    }
  }
  {
    /*test row-major order*/
    /*           x = 0   1   2   3 */
    int values[] = {
        /*y=0*/ 11, 21, 31, 41,
        /*y=1*/ 12, 22, 32, 42,
        /*y=2*/ 13, 23, 33, 43,
        /*y=3*/ 14, 24, 34, 44,
        /*y=4*/ 15, 25, 35, 45,
    };
    matrix<int> test_data(4, 5);
    for (size_t i = 0; i < (sizeof(values) / sizeof(values[0])); i++) {
      //            debug_log(i);
      test_data(i) = values[i];
    }
    for (int x = 0; x < 4; x++) {
      for (int y = 0; y < 5; y++) {
        test(test_data(x, y) == 10 * (x + 1) + (y + 1), "ordering");
        /*test debugging code*/
        //                std::cout << "test_data(" << x << "," << y << ") = "
        //                <<
        //                std::setw(5) << test_data(x, y) << " need " <<
        //                std::setw(5) << 10 * (x + 1) + (y + 1);
        //                if (test_data(x, y) == 10 * (x + 1) + (y + 1)) {
        //                    std::cout << " pass" << std::endl;
        //                } else {
        //                    std::cout << " fail" << std::endl;
        //                }
      }
    }
  }
  {
    /*equality operators*/
    matrix<int> mat1(3, 3);
    matrix<int> mat2(3, 3);
    matrix<int> mat3(3, 3);
    matrix<int> mat4(3, 8);
    for (int i = 0; i < 9; i++) {
      mat1((size_t)i) = i * i;
      mat2((size_t)i) = i * i;
      mat3((size_t)i) = i * i;
      mat4((size_t)i) = i * i;
    }
    mat3(3) = 0;
    test(mat1 == mat2, "equality");
    test(!(mat1 != mat2), "equality");
    test(mat1 != mat3, "inequality");
    test(!(mat1 == mat3), "inequality");
    test(mat1 != mat4, "inequality");
    test(!(mat1 == mat4), "inequality");
  }
  {
    /*test other (C++ style) allocators*/
    matrix<int, Mallocator<int>> matrix1_malloc(5, 5);
    matrix<int, Mallocator<int>>matrix2_malloc(5, 5);
    matrix<int, Mallocator<int>> matrix3(5, 5);
    matrix1_malloc.fill(0);
    matrix2_malloc.fill(1);
    matrix3.fill(3);

    matrix1_malloc = matrix3;
    test(matrix1_malloc == matrix3, "external allocator");
    matrix3 = matrix2_malloc;
    test(matrix2_malloc == matrix3, "external allocator");

    matrix2_malloc.fill(30);
    matrix3.fill(~30);
    std::copy_n(matrix3.data(), matrix3.size(), matrix2_malloc.begin());
    test(matrix2_malloc == matrix3, "external allocator");
  }
  {
    matrix<int> mat({
        {1, 2, 3}, {4, 5, 6}, {7, 8, 9},
    });
    test(mat(0, 0) == 1, "first row");
    test(mat(1, 1) == 5, "second row");
    test(mat(2, 2) == 9, "third row");
  }
}
