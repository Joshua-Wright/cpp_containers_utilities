// (c) Copyright 2015 Josh Wright

#include <iostream>
#include <string.h>
#include <libgen.h> // for basename()
#include "../lib/array_list.h"

void test(bool expr, const std::string &message, const char* file, int line) {
    if (!expr) {
        char* new_str = new char[strlen(file) + 1];
        strcpy(new_str, file);
        std::cout << basename(new_str) << ":"<< line << "  Test failed: " << message << std::endl;
    }
}
#define test(x,y) test(x,y, __FILE__, __LINE__)

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
        test(false, "a");
        al1.push_back(2);
        al1.push_back(3);
        al1.push_back(4);
        cout << al1.front() << endl;
        test(al1.front() == 5, "front()");
        test(al1.back() == 4, "back()");
    }

    return 0;
}
