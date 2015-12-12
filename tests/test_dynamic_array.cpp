// (c) Copyright 2015 Josh Wright
#include <iostream>
#include <cassert>
#include "../lib/dynamic_array.h"

// (c) Copyright 2015 Josh Wright
int main(int argc, char const *argv[]) {
    using containers::dynamic_array;
    {
        /*test default values*/
        dynamic_array<int> test_array(50, 1);
        assert(test_array[1] == 1);
        assert(test_array[5] == 1);
        assert(test_array[49] == 1);
    }
    {
        /*test default default values*/
        dynamic_array<double> test_array(50);
        assert(test_array[1] == 0);
        assert(test_array[5] == 0);
        assert(test_array[49] == 0);
    }
    {
        /*test assignment*/
        dynamic_array<long> test_array(25);
        test_array[4] = 70;
        test_array[8] = 90.25;
        test_array[2] = 7;
        test_array[2] *= 2;
        assert(test_array[4] == 70);
        assert(test_array[8] == 90);
        assert(test_array[2] == 14);
    }
    {
        /*test append*/
        dynamic_array<long> test_array(1);
        test_array[0] = 1;
        test_array.append(2);
        test_array.append(3);
        assert(test_array[0] == 1);
        assert(test_array[1] == 2);
        assert(test_array[2] == 3);
    }
    {
        std::size_t size = 200;
        /*test array element-wise operations*/
        dynamic_array<long> test_array_1(size, 0);
        dynamic_array<long> test_array_2(size, 0);
        dynamic_array<long> test_array_3(size, 0);
        dynamic_array<long> test_array_4(size, 0);
        dynamic_array<long> test_array_5(size, 0);
        for (int i = 0; i < size; i++) {
            test_array_1[i] = i;
            test_array_2[i] = i;
            test_array_3[i] = i;
            test_array_4[i] = i;
            test_array_5[i] = i;
        }

        test_array_1 *= 4;
        test_array_2 /= 4;
        test_array_3 += 4;
        test_array_4 -= 4;
        test_array_5 %= 4;

        for (int i = 0; i < 5; i++) {
            assert(test_array_1[i] == i * 4);
            assert(test_array_2[i] == i / 4);
            assert(test_array_3[i] == i + 4);
            assert(test_array_4[i] == i - 4);
            assert(test_array_5[i] == i % 4);
        }
    }
    {
        /*test array-array operations*/
        dynamic_array<long> test_array_0(5, 7);
        dynamic_array<double> test_array_1(5, 0);
        dynamic_array<char> test_array_2(5, 0);
        dynamic_array<unsigned> test_array_3(5, 0);
        dynamic_array<unsigned long> test_array_4(5, 0);
        for (int i = 0; i < 5; i++) {
            test_array_1[i] = i;
            test_array_2[i] = i;
            test_array_3[i] = i;
            test_array_4[i] = i;
        }

        test_array_1 *= test_array_0;
        test_array_2 /= test_array_0;
        test_array_3 += test_array_0;
        test_array_4 -= test_array_0;

        for (int i = 0; i < 5; i++) {
            assert(test_array_1[i] == i * test_array_0[i]);
            assert(test_array_2[i] == i / test_array_0[i]);
            assert(test_array_3[i] == i + test_array_0[i]);
            assert(test_array_4[i] == i - test_array_0[i]);
        }
    }
    {
        /*various assignments and constructions*/
        dynamic_array<int> test_array_1(20, 1234);
        dynamic_array<int> test_array_2 = test_array_1;
        dynamic_array<int> test_array_3(test_array_1);
        dynamic_array<int> test_array_4;
        const dynamic_array<int> test_array_5(test_array_1);
        test_array_4 = test_array_1;
        for (int i = 0; i < 20; i++) {
            assert(test_array_1[i] == 1234);
            assert(test_array_2[i] == 1234);
            assert(test_array_3[i] == 1234);
            assert(test_array_4[i] == 1234);
            assert(test_array_5[i] == 1234);
        }

    }
    {
        /*test equality*/
        dynamic_array<int> test_array_1(20, 1234);
        dynamic_array<int> test_array_2 = test_array_1;
        assert(test_array_1 == test_array_2);
        test_array_1[3] = 888;
        assert(test_array_1 != test_array_2);
    }
    {
        /*test resize*/
        dynamic_array<int> test_array_1(10, 1234);
        test_array_1.resize(20);
        test_array_1[15] = 999;
        assert(test_array_1[5] = 1234);
        assert(test_array_1[15] = 999);
    }

}
