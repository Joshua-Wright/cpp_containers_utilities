// (c) Copyright 2015 Josh Wright
#include <iostream>
#include "../lib/binary_search_tree.h"

void test(bool expr, const std::string &message) {
    if (!expr) {
        std::cout << "Test failed: " << message << std::endl;
    }
}


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

    return 0;
}
