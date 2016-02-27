// (c) Copyright 2015 Josh Wright
#pragma once

#include <iostream>
#include <cstring> // for strlen()
#include <libgen.h> // for basename()

template<typename T>
void debug_log(T var, const char* label, const char *file, int line) {
    char *new_str = new char[strlen(file) + 1];
    strcpy(new_str, file);
    std::cout << basename(new_str) << ":" << line << " " << label << "=" << var << std::endl;
}
#define debug_log(x) log(x, #x, __FILE__, __LINE__)


void test(bool expr, const std::string &message, const char *file, int line) {
    if (!expr) {
        char *new_str = new char[strlen(file) + 1];
        strcpy(new_str, file);
        std::cout << basename(new_str) << ":" << line << "  Test failed: " <<
        message << std::endl;
    }
}
#define test(x, y) test(x,y, __FILE__, __LINE__)
