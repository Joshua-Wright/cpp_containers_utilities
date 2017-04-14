// (c) Copyright 2016 Josh Wright
// helpful snippets for debugging C++ programs
// These abuse macros, templates and operator overloads
// to make them easier to use
#pragma once

#include "preprocessor_utils.h"
#include <iomanip>
#include <iostream>
#include <malloc.h>
#include <sstream>
#include <typeinfo>
#include <vector>

#ifndef DEBUG_USE_BASENAME
#include <cstring>
#define DEBUG_USE_BASENAME 1
#endif

#ifndef DEMANGLE
#define DEMANGLE 1
#include <cxxabi.h> // for abi::__cxa_demangle()
#endif

namespace __hidden__ {

using std::cerr;
using std::endl;
using std::setw;
using std::left;

struct print {
    bool space;
    const char *expr;
    const char *file;
    int line;

    print(const char *file, int line, const char *expr) : space(false), expr(expr), file(file), line(line) {}

    ~print() { cerr << endl; }

    template <typename T>
    print &operator,(const T &t) {
        if (space) {
            cerr << ' ';
        } else {
            cerr <<
#if DEBUG_USE_BASENAME
                basename(file)
#else
                file
#endif
                 << ":" << line << " " << expr << " = ";
            space = true;
        }
        cerr << t;
        return *this;
    }
};

template <typename T>
std::string demangle_type_name() {
    if (typeid(T) == typeid(std::string)) {
        return "std::string";
    } else {
#if DEMANGLE
        /*gcc-specific way to de-mangle the type names, probably not portable*/
        char *n = abi::__cxa_demangle(typeid(T).name(), NULL, NULL, NULL);
#else
        char *n = typeid(T).name();
#endif
        std::string name(n);
        free(n);
        return name;
    }
}

template <typename T>
void __debug_log(T v, const char *l, const char *f, int line, bool p) {
    /*debug logger that uses template type resolution to print whatever we give it*/
    cerr <<
#if DEBUG_USE_BASENAME
        basename(f)
#else
        f
#endif
         << ":" << line << " ";
    if (p) {
        cerr << demangle_type_name<T>() << " ";
    }
    cerr << l << "=" << v << endl;
}

struct key_value_printer {
    struct line {
        std::string type;
        std::string key;
        std::string value;
    };
    std::vector<line> lines;
    const char *expr;
    const char *file;
    int line;

    key_value_printer(const char *file, int line) : file(file), line(line) {}

    template <typename T>
    key_value_printer &a(const std::string &key, const T &value) {
        std::stringstream val;
        val << value;
        lines.push_back({demangle_type_name<T>(), key, val.str()});
        return *this;
    }

    ~key_value_printer() {
        size_t max_name_length = 0;
        size_t max_type_length = 0;
        for (auto &l : lines) {
            if (l.key.length() > max_name_length) {
                max_name_length = (int)l.key.length();
            }
            if (l.type.length() > max_type_length) {
                max_type_length = (int)l.type.length();
            }
        }
        cerr << basename(file) << ":" << line << ":" << endl;
        for (auto &l : lines) {
            cerr << setw((int)max_type_length) << left << l.type
                 << " : "
                 << setw((int)max_name_length) << left << l.key
                 << " = "
                 << l.value << endl;
        }
    }
};
}

#define __KV_0 __hidden__::key_value_printer(__FILE__, __LINE__)
#include "__generated/debug.h"

#define KV_MULTIPLE(N, ...) __KV_##N(__VA_ARGS__)
// the following is necessary to make sure the processor has a chance to evaluate NARG16
#define _KV_MULTIPLE(N, ...) KV_MULTIPLE(N, __VA_ARGS__)
#define KV(...) _KV_MULTIPLE(NARG(__VA_ARGS__), __VA_ARGS__)


#define DEBUG_LOG(x) __hidden__::__debug_log(x, #x, __FILE__, __LINE__, true)
#define DEBUG_LOG_TYPE(x) __hidden__::__debug_log(x, #x, __FILE__, __LINE__, true)
#define DEBUG_LOG_NOTYPE(x) __hidden__::__debug_log(x, #x, __FILE__, __LINE__, false)

#define DEBUG_PRINT(...) __hidden__::print(__FILE__, __LINE__, (#__VA_ARGS__)), __VA_ARGS__;
