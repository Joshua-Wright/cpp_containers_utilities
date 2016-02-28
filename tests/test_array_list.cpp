// (c) Copyright 2015 Josh Wright

#include <iostream>
#include <string.h>
#include "../lib/debug.h"
#include "../lib/array_list.h"

int main() {
    using std::cout;
    using std::endl;
    {
        array_list<int> al1;
        test(al1.empty(), "constructor");
    }
    {
        array_list<int> al1;
        al1.push_back(5);
        test(!al1.empty(), "push_back()");
        test(al1.front() == 5, "front()");
        test(al1.back() == 5, "back()");
        al1.push_back(2);
        al1.push_back(3);
        al1.push_back(4);
        test(al1.front() == 5, "front()");
        test(al1.back() == 4, "back()");
        test(al1.size() == 4, "size()");
        al1.push_front(2);
        al1.push_front(3);
        al1.push_front(4);
        al1.push_back(123);
        test(al1.front() == 4, "front()");
        test(al1.back() == 123, "back()");
        test(al1.size() == 8, "size()");
    }
    {
        array_list<int> al1;
        al1.push_back(1);
        al1.push_back(2);
        al1.push_back(3);
        al1.push_back(4);
        test(al1.size() == 4, "pop_back() size");
        al1.pop_back();
        test(al1.back() == 3, "pop_back()");
        al1.pop_back();
        test(al1.back() == 2, "pop_back()");
        al1.pop_back();
        test(al1.back() == 1, "pop_back()");
        test(al1.size() == 1, "pop_back() size");
        al1.push_back(2);
        al1.push_back(3);
        al1.push_back(4);
        test(al1.size() == 4, "pop_front()");
        al1.pop_front();
        test(al1.front() == 2, "pop_front()");
        al1.pop_front();
        test(al1.front() == 3, "pop_front()");
        al1.pop_front();
        test(al1.front() == 4, "pop_front()");
        test(al1.size() == 1, "pop_front()");
    }
    {
        array_list<int> al1;
        for (int i = 0; i < 5; i++) {
            al1.push_back(i);
        }
        auto it1 = al1.begin();
        for (int i = 0; i < 5; ++i) {
            test(*it1 == i, "iterators");
            ++it1;
        }
        auto it2 = --al1.end();
        for (int i = 4; i >= 0; --i) {
            test(*it2 == i, "iterators");
            --it2;
        }
    }
    {
        std::initializer_list<char> il1{1, 2, 3, 65, 1, 3, -123, 123, 4, 2, -3,
                                        2, 1, 43};
        array_list<char> al1{1, 2, 3, 65, 1, 3, -123, 123, 4, 2, -3, 2, 1, 43};
        test(std::equal(al1.begin(), al1.begin(), il1.begin()), "init. list");
        test(std::equal(il1.begin(), il1.begin(), al1.begin()), "init. list");
    }
    {
        array_list<char> al1{1, 2, 3, 4, 5};
        auto it1 = al1.begin();
        while (it1 != al1.end()) {
            if (((*it1) % 2) == 0) {
                al1.insert(it1, 123);
                ++it1;
            }
            ++it1;
        }
        al1.insert(--al1.end(), 34);
        al1.insert(al1.end(), 99);
        std::initializer_list<char> il1{1, 2, 123, 3, 4, 123, 5, 34, 99};
        test(std::equal(al1.begin(), al1.begin(), il1.begin()), "insert");
        test(std::equal(il1.begin(), il1.begin(), al1.begin()), "insert");
    }
    {
        array_list<double> al1(23, 123.0);
        test(al1.size() == 23, "size-value constructor");
        for (auto &a : al1) {
            test(a == 123.0, "size-value constructor");
        }
    }
    {
        array_list<char> al1{1, 2, 3, 4, 5, 6, 7, 8, 9};
        test(al1.size() == 9, "erase");
        auto it3 = al1.begin();
        it3 += 3;
        al1.erase(it3);
        auto it1 = al1.begin();
        al1.erase(it1);
        auto it2 = --al1.end();
        al1.erase(it2);
        /*should not allow erasing at past-end iterator*/
        al1.erase(al1.end());
        std::initializer_list<char> il1{2, 3, 5, 6, 7, 8};
        test(al1.size() == 6, "erase");
        test(std::equal(al1.begin(), al1.begin(), il1.begin()), "erase");
        test(std::equal(il1.begin(), il1.begin(), al1.begin()), "erase");
    }

    return 0;
}
