// (c) Copyright 2016 Josh Wright
#include <iostream>
#include <cassert>
#include <iomanip>
#include "../lib/matrix.h"
#include "../lib/debug.h"

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
    {
        /*test row-major order*/
        /*           x = 0    1    2    3 */
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
        for (size_t x = 0; x < 4; x++) {
            for (size_t y = 0; y < 5; y++) {
                test(test_data(x, y) == 10 * (x + 1) + (y + 1), "ordering");
                /*test debugging code*/
//                std::cout << "test_data(" << x << "," << y << ") = " <<
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
        matrix<int> mat1(3,3);
        matrix<int> mat2(3,3);
        matrix<int> mat3(3,3);
        matrix<int> mat4(3,8);
        for (int i=0; i<9; i++) {
            mat1(i) = i*i;
            mat2(i) = i*i;
            mat3(i) = i*i;
            mat4(i) = i*i;
        }
        mat3(3) = 0;
        test(mat1 == mat2, "equality");
        test(!(mat1 != mat2), "equality");
        test(mat1 != mat3, "inequality");
        test(!(mat1 == mat3), "inequality");
        test(mat1 != mat4, "inequality");
        test(!(mat1 == mat4), "inequality");
    }

}
