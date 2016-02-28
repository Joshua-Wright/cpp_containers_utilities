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

    return 0;
}
