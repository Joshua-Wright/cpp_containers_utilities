#pragma once
#include <iostream>

#define __TESTING__TEST__(x, msg, file, line)                      \
  if (!(x)) {                                                      \
    std::cerr << file << ":" << line << " " << (msg) << std::endl; \
    return 1;                                                      \
  }
#define test(x, msg) __TESTING__TEST__(x, msg, __FILE__, __LINE__)
