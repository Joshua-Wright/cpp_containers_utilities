// (c) Copyright 2015 Josh Wright


#include <iostream>
#include <cassert>
#include <thread>
#include <mutex>
#include "../lib/debug.h"
#include "../lib/double_linked_list.h"

int main() {
    /*template:
    {
        std::string test("");
        try {
        } catch (...) { std::cout << "Test failed: " << test << std::endl; }
    }
    */
    {
        std::string current_test("Constructor");
        try {
            double_linked_list<int> linked_list1;
            double_linked_list<double> linked_list2;
            /*mutexes can't be copied*/
            double_linked_list<std::mutex> linked_list3;
        } catch (...) { std::cout << "Test failed: " << current_test << std::endl; }
    }
    {
        double_linked_list<int> linked_list1;
        test(linked_list1.empty(), "empty()");
    }
    {
        double_linked_list<int> linked_list1;
        linked_list1.push_back(1);
        linked_list1.push_front(121);
        linked_list1.clear();
        test(linked_list1.empty(), "clear()");
    }
    {
        double_linked_list<int> linked_list1;
        linked_list1.push_back(1);
        linked_list1.push_back(2);
        linked_list1.push_back(3);
        linked_list1.push_back(4);
        linked_list1.pop_back();
        linked_list1.pop_front();
        test(linked_list1.front() == 2, "pop");
        test(linked_list1.back() == 3, "pop");
    }
    {
        double_linked_list<int> linked_list1;
        linked_list1.push_front(5);
        linked_list1.push_front(7);
        linked_list1.push_front(2);
        test(!linked_list1.empty(), "empty()");
        double_linked_list<int> linked_list2(linked_list1);
        double_linked_list<int> linked_list3 = linked_list1;

        test(std::equal(linked_list2.begin(), linked_list2.end(),
                        linked_list1.begin()), "copy assignment");
        test(std::equal(linked_list3.begin(), linked_list3.end(),
                        linked_list1.begin()), "copy constructor");
    }
    {
        double_linked_list<int> linked_list1;
        linked_list1.push_front(1325);
        test(linked_list1.front() == 1325, "push_front() and front()");
        test(linked_list1.back() == 1325, "push_front() and back()");
        linked_list1.push_front(1);
        linked_list1.push_front(2);
        linked_list1.push_front(3);
        test(linked_list1.front() == 3, "push_front() and front()");
        test(linked_list1.back() == 1325, "push_front() and back()");
        linked_list1.push_back(7);
        test(linked_list1.back() == 7, "push_back() and back()");
    }
    {
        double_linked_list<int> linked_list1;
        linked_list1.push_front(1);
        test(*(linked_list1.begin()) == 1, "iterator dereference");
        test(*(linked_list1.end()) == 1, "iterator dereference");
    }
    {
        double_linked_list<int> ll1{1, 2, 3, 4};
        double_linked_list<int>::iterator g = ll1.begin();
        double_linked_list<int>::iterator h = ll1.end();
        g += 2;
        h -= 2;
        test(*(ll1.begin()) == 1, "iterator dereference");
        test(*(ll1.end()) == 4, "iterator dereference");
        test(*g == 3, "iterator addition");
        test(*h == 2, "iterator addition");
    }
    {
        double_linked_list<int> linked_list1;
        double_linked_list<int> linked_list2;
        for (int i = 0; i <= 300; i++) {
            linked_list1.push_front(i);
            linked_list2.push_front(i);
            linked_list1.push_back(i * i);
            linked_list2.push_back(i * i);
        }
        bool equal = true;
        auto i1 = linked_list1.begin();
        auto i2 = linked_list2.begin();
        while (i1 != linked_list1.end() && i2 != linked_list2.end()) {
            equal = (*i1 == *i2);
            ++i1;
            ++i2;
        }
        test(equal, "iterators");
        test(!linked_list1.empty(), "iterators empty 1");
        test(!linked_list2.empty(), "iterators empty 2");
    }
    {
        double_linked_list<int> l1;
        double_linked_list<int> l2;
        for (int i = 0; i <= 300; i++) {
            l1.push_front(i);
            l2.push_front(i);
            l1.push_back(i * i);
            l2.push_back(i * i);
        }
        test(l1 == l2, "== operator");
        l1.push_back(1);
        test(l1 != l2, "!= operator 1");
        test(l2 != l1, "!= operator 2");
        l1.pop_back();
        l2.push_back(1);
        test(l1 != l2, "!= operator 3");
        test(l2 != l1, "!= operator 4");
    }
    {
        double_linked_list<int> l1{1, 2, 3, 4};
        double_linked_list<int> l2 = {1, 2, 3, 4};
        double_linked_list<int> l3;
        l3 = {1, 2, 3, 4};
        test(l1.front() == 1, "initializer list");
        test(l2.front() == 1, "initializer list");
    }
    {
        double_linked_list<int> l1{1, 2, 3, 4};
        double_linked_list<int>::iterator it = l1.begin();
        it++;
        it++;
        l1.insert_after(it, 9);
        l1.insert_before(it, 99);
        double_linked_list<int> l2{1, 2, 99, 3, 9, 4};
        test(l1 == l2, "insert after and before");
    }


    return 0;
}
