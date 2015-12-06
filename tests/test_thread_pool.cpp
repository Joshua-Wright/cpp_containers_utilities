// (c) Copyright 2015 Josh Wright
#include <iostream>
#include "../lib/thread_pool.h"
#include "../lib/matrix.h"
#include "test_thread_pool.h"

using containers::matrix;

struct rose_dist : functor_class<long double> {
    long double n;
    long double x;
    long double y;

    rose_dist(long double _n, long double _x, long double _y) : n(_n), x(_x), y(_y) { };

    rose_dist(long double _n) : n(_n), x(0.0L), y(0.0L) { };

    virtual long double operator()(const long double &t) {
        return pow(cos(n * t) * cos(t) - x, 2) +
               pow(cos(n * t) * sin(t) - y, 2);
    }

    virtual long double diff(const long double &t) {
        long double cos_t = cos(t);
        long double sin_t = sin(t);
        long double cos_nt = cos(n * t);
        long double sin_nt = sin(n * t);
        return -2 * n * cos_nt * cos_t * cos_t * sin_nt
               - 2 * n * cos_nt * sin_nt * sin_t * sin_t
               + 2 * n * x * cos_t * sin_nt
               + 2 * n * y * sin_nt * sin_t
               - 2 * y * cos_nt * cos_t
               + 2 * x * cos_nt * sin_t;
    }
};

long double function_min(functor_class<long double> *func, const long double a, const long double b,
                         const int steps = 100, const int rounds = 999) {
    if ((b - a) < sqrt(std::numeric_limits<long double>::epsilon()) || rounds <= 0) {
        return (*func)((a + b) / 2);
    }
    long double step = (b - a) / steps;
    long double l_t = a;
    long double r_t = a + step;
    long double l_diff = func->diff(l_t);
    long double r_diff = func->diff(r_t);
    long double current_min = (*func)(b);
    long double current_val;
    while (l_t < b) {
        if (l_diff < 0 && r_diff > 0) {
            current_val = function_min(func, l_t, r_t, steps, rounds - 1);
            if (current_val < current_min) {
                current_min = current_val;
            }
        }
        l_t = r_t;
        l_diff = r_diff;
        r_t += step;
        r_diff = func->diff(r_t);
    }
    return current_min;
}

int main(int argc, char const *argv[]) {
    using namespace containers;
    long double z = 200;
    matrix<long double> test_matrix(z, z);
    auto thread_func = [z](std::size_t x, std::size_t y) {
        rose_dist dist_func(0.25, (x - z / 2) / z, (y - z / 2) / z);
        return function_min(&dist_func, 0, 30);
    };
    function_mapper_thread<decltype(thread_func), long double> func_mapper(thread_func, test_matrix);
    thread_pool_func(func_mapper, 3);
    return 0;
}
