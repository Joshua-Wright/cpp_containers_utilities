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
        /*test array operations*/
        dynamic_array<long> test_array_1(5, 0);
        dynamic_array<long> test_array_2(5, 0);
        dynamic_array<long> test_array_3(5, 0);
        dynamic_array<long> test_array_4(5, 0);
        for (int i = 0; i < 5; i++) {
            test_array_1[i] = i;
            test_array_2[i] = i;
            test_array_3[i] = i;
            test_array_4[i] = i;
        }

        test_array_1 *= 4;
        test_array_2 /= 4;
        test_array_3 += 4;
        test_array_4 -= 4;

        for (int i = 0; i < 5; i++) {
            assert(test_array_1[i] == i * 4);
            assert(test_array_2[i] == i / 4);
            assert(test_array_3[i] == i + 4);
            assert(test_array_4[i] == i - 4);
        }
    }
}
