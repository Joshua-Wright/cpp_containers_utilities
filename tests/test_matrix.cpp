// (c) Copyright 2015 Josh Wright
#include <iostream>
#include <cassert>
#include "../lib/matrix.h"

int main(int argc, char const *argv[]) {
    using containers::matrix;
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
        std::size_t x = 20;
        std::size_t y = 20;
        /*test array element-wise operations*/
        matrix<long> test_array_1(x, y, 0);
        matrix<long> test_array_2(x, y, 0);
        matrix<long> test_array_3(x, y, 0);
        matrix<long> test_array_4(x, y, 0);
        matrix<long> test_array_5(x, y, 0);
        for (int i = 0; i < x; i++) {
            for (int j = 0; j < y; j++) {
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

        for (int i = 0; i < x; i++) {
            for (int j = 0; j < y; j++) {
                assert(test_array_1(i, j) == (i * j - i) * 4);
                assert(test_array_2(i, j) == (i * j - i) / 4);
                assert(test_array_3(i, j) == (i * j - i) + 4);
                assert(test_array_4(i, j) == (i * j - i) - 4);
                assert(test_array_5(i, j) == (i * j - i) % 4);
            }
        }
    }

}
