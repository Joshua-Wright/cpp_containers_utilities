// (c) Copyright 2016-2017 Josh Wright
// helpful snippets for debugging C++ programs
// These abuse macros, templates and operator overloads
// to make them easier to use
#pragma once

#ifdef _MSC_VER

// MSVC does not expand __VA_ARGS__ correctly,
// so this stuff doesn't work
#define KV(...)
#define DEBUG_LOG(x)
#define DEBUG_LOG_TYPE(x)
#define DEBUG_LOG_NOTYPE(x)
#define DEBUG_PRINT(...)

#else


#include "__generated/debug.h"
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

#ifdef __GNUC__
#define DEBUG_FUNC_NAME __PRETTY_FUNCTION__
#else
#define DEBUG_FUNC_NAME __func__
#endif

#if !defined(DEBUG_DEMANGLE) && defined(__cpp_rtti)
#define DEBUG_DEMANGLE 1
#include <cxxabi.h> // for abi::__cxa_demangle()
#endif

namespace {

struct print {
    bool space;
    const char *expr;
    const char *file;
    int line;

    print(const char *file, int line, const char *expr) : space(false), expr(expr), file(file), line(line) {}

    ~print() { std::cerr << std::endl; }

    template <typename T>
    print &operator,(const T &t) {
        if (space) {
            std::cerr << ' ';
        } else {
            std::cerr <<
#if DEBUG_USE_BASENAME
                basename(file)
#else
                file
#endif
                      << ":" << line << expr << " = ";
            space = true;
        }
        std::cerr << t;
        return *this;
    }
};

template <typename T>
std::string demangle_type_name() {
#if defined(__cpp_rtti)
    if (typeid(T) == typeid(std::string)) {
        return "std::string";
    } else {
#if DEBUG_DEMANGLE
        /*gcc-specific way to de-mangle the type names, probably not portable*/
        char *n = abi::__cxa_demangle(typeid(T).name(), NULL, NULL, NULL);
#else
        char *n = typeid(T).name();
#endif
        std::string name(n);
        free(n);
        return name;
    }
#else
    return "";
#endif
}

template <typename T>
void __debug_log(T v, const char *l, const char *f, int line, const char *func, bool p) {
    /*debug logger that uses template type resolution to print whatever we give it*/
    std::cerr <<
#if DEBUG_USE_BASENAME
        basename(f)
#else
        f
#endif
              << ":" << line << " in " << func << " ";
    if (p) {
        std::cerr << demangle_type_name<T>() << " ";
    }
    std::cerr << l << "=" << v << std::endl;
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
#if DEBUG_USE_BASENAME
        std::cerr << basename(file) << ":" << line << ":" << std::endl;
#else
        std::cerr << file << ":" << line << ":" << std::endl;
#endif
        for (auto &l : lines) {
            std::cerr << std::setw((int)max_type_length) << std::left << l.type
                      << " : "
                      << std::setw((int)max_name_length) << std::left << l.key
                      << " = "
                      << l.value << std::endl;
        }
    }
};
}

#define __KV_0 ::key_value_printer(__FILE__, __LINE__)

#define KV_MULTIPLE(N, ...) __KV_##N(__VA_ARGS__)
// the following is necessary to make sure the processor has a chance to evaluate DEBUG_NARG16
#define _KV_MULTIPLE(N, ...) KV_MULTIPLE(N, __VA_ARGS__)
#define KV(...) _KV_MULTIPLE(DEBUG_NARG(__VA_ARGS__), __VA_ARGS__)


#define DEBUG_LOG(x) ::__debug_log(x, #x, __FILE__, __LINE__, DEBUG_FUNC_NAME, true)
#define DEBUG_LOG_TYPE(x) ::__debug_log(x, #x, __FILE__, __LINE__, DEBUG_FUNC_NAME, true)
#define DEBUG_LOG_NOTYPE(x) ::__debug_log(x, #x, __FILE__, __LINE__, DEBUG_FUNC_NAME, false)

#define DEBUG_PRINT(...) ::print(__FILE__, __LINE__, (#__VA_ARGS__)), __VA_ARGS__;

#endif // ifdef _MSC_VER