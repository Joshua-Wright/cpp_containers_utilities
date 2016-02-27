// (c) Copyright 2015 Josh Wright
#include <iostream>
#include <vector>
#include <algorithm>
#include "../lib/debug.h"
#include "../lib/binary_search_tree.h"


int main() {

    {
        binary_search_tree<double> b1;
        test(b1.empty(), "empty()");
        test(b1.size() == 0, "size()");
    }


    {
        binary_search_tree<int> b1;
        b1.insert(5);
        test(!b1.empty(), "insert()");
        test(b1.contains(5), "contains() 1");
    }
    {
        binary_search_tree<int> b1;
        for (int i = 0; i < 30; i++) {
            b1.insert((i * i) % 10);
        }
        test(!b1.empty(), "insert()");
        for (int i :  {0, 1, 4, 5, 6, 9}) {
            test(b1.contains(i), "contains()");
        }
        for (int i: {2, 3, 7, 8}) {
            test(!b1.contains(i), "not contains()");
        }
    }

    {
        binary_search_tree<int> b1;
        std::vector<int> test_values{6, 2, 8, 1, 4, 7, 10, 3, 5, 9};
        for (int i : test_values) {
            b1.insert(i);
        }
        std::sort(test_values.begin(), test_values.end());

        /*for debugging*/
//        size_t count = 0;
//        for (int i : b1) {
//            std::cout << i << "," << test_values[count] << " ";
//            ++count;
//            if (count > 15) {
//                break;
//            }
//        }
//        std::cout << std::endl;
        test(std::equal(b1.begin(), b1.end(), test_values.begin()),
             "iterators 1");
        test(std::equal(test_values.begin(), test_values.end(), b1.begin()),
             "iterators 2");
    }

    {
        binary_search_tree<int> b1;
        std::vector<int> test_values{6, 2, 8, 1, 4, 7, 10, 3, 5, 9};
        for (int i : test_values) {
            b1.insert(i);
        }
        std::sort(test_values.begin(), test_values.end());
        b1.remove(1);
        test_values.erase(test_values.begin());
        test(std::equal(b1.begin(), b1.end(), test_values.begin()),
             "remove() 1");
        test(std::equal(test_values.begin(), test_values.end(), b1.begin()),
             "remove() 2");
    }

    return 0;
}
