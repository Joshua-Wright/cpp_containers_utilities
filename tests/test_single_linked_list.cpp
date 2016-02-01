// (c) Copyright 2015 Josh Wright

#include <iostream>
#include <cassert>
#include <thread>
#include <mutex>
#include "../lib/single_linked_list.h"

void test(bool expr, const std::string &message) {
    if (!expr) {
        std::cout << "Test failed: " << message << std::endl;
    }
}


//int main(int argc, char const *argv[]) {
/*don't have arguments so g++ doesn't complain*/
int main() {

    {
        std::string test("Constructor");
        try {
            single_linked_list<int> linked_list1;
            single_linked_list<double> linked_list2;
            /*mutexes can't be copied*/
            single_linked_list<std::mutex> linked_list3;
        } catch (...) { std::cout << "Test failed: " << test << std::endl; }
    }
    {
        single_linked_list<int> linked_list1;
        test(linked_list1.empty(), "empty()");
    }
    {
        single_linked_list<int> linked_list1;
        linked_list1.push_back(1);
        linked_list1.push_front(121);
        linked_list1.clear();
        test(linked_list1.empty(), "clear()");
    }
    {
        single_linked_list<int> linked_list1;
        linked_list1.push_back(1);
        linked_list1.push_back(2);
        linked_list1.push_back(3);
        linked_list1.push_back(4);
        linked_list1.pop_front();
        test(linked_list1.front() == 2, "pop");
        test(linked_list1.back() == 4, "pop");
    }
    {
        single_linked_list<int> linked_list1;
        linked_list1.push_front(5);
        linked_list1.push_front(7);
        linked_list1.push_front(2);
        test(!linked_list1.empty(), "empty()");
        single_linked_list<int> linked_list2(linked_list1);
        single_linked_list<int> linked_list3 = linked_list1;

        test(std::equal(linked_list2.begin(), linked_list2.end(),
                        linked_list1.begin()), "copy assignment");
        test(std::equal(linked_list3.begin(), linked_list3.end(),
                        linked_list1.begin()), "copy constructor");
    }
    {
        single_linked_list<int> linked_list1;
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
        single_linked_list<int> linked_list1;
        linked_list1.push_front(1);
        test(*(linked_list1.begin()) == 1, "iterator dereference");
        test(*(linked_list1.end()) == 1, "iterator dereference");
    }
    {
        single_linked_list<int> linked_list1;
        single_linked_list<int> linked_list2;
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
        single_linked_list<int> l1;
        single_linked_list<int> l2;
        for (int i = 0; i <= 300; i++) {
            l1.push_front(i);
            l2.push_front(i);
            l1.push_back(i * i);
            l2.push_back(i * i);
        }
        test(l2 == l2, "== operator");
        test(l1 == l1, "== operator");
        test(l1 == l2, "== operator");
        test(l2 == l1, "== operator");
        l1.push_back(1);
        test(l1 != l2, "!= operator 1");
        test(l2 != l1, "!= operator 2");
        test(! (l2 != l2), "!= operator 3");
        test(! (l1 != l1), "!= operator 4");
    }
    {
        single_linked_list<int> l1{1,2,3,4};
        single_linked_list<int> l2 = {1,2,3,4};
        single_linked_list<int> l3;
        l3 = {1,2,3,4};
        test(l1.front() == 1, "initializer list");
        test(l2.front() == 1, "initializer list");
    }
    {
        single_linked_list<int> l1{1,2,3,4};
        single_linked_list<int>::iterator it = l1.begin();
        it++;
        it++;
        l1.insert_after(it, 9);
        single_linked_list<int> l2{1,2,3,9,4};
        test(l1 == l2, "insert after and before");
    }

    return 0;
}
