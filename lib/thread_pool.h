//
// Created by j0sh on 12/5/15.
//

#ifndef CONTAINERS_THREAD_POOL_H
#define CONTAINERS_THREAD_POOL_H

#include <atomic>
#include <thread>
#include <list>
#include "matrix.h"


namespace containers {

    template<class F, typename T>
    class function_mapper_thread {
        F function;
        matrix<T> mat;
    public:
        function_mapper_thread(F function, matrix<T> m) : function(function), mat(m) { };

        void operator()(std::atomic_ullong &current_index) {
            unsigned long long our_current_index;
            while ((our_current_index = current_index.fetch_add(1)) < mat.size()) {
                std::size_t x = mat.z_to_x(our_current_index);
                std::size_t y = mat.z_to_y(our_current_index);
                mat(x, y) = function(x, y);
            }
        };
    };


    template<class F>
    class thread_pool {

        F function;
        std::atomic_ullong current_index;

        std::list<std::thread> threads;

        int n_threads;

    public:
        thread_pool(F function, int n_threads) : function(function), current_index(0),
                                                 n_threads(n_threads) { };

        void execute() {
            for (int i = 0; i < n_threads; i++) {
                threads.emplace_back(function, std::ref(current_index));
            }
            for (auto &t : threads) {
                t.join();
            }
        }

    };


    template<class F>
    void thread_pool_func(F function, int n_threads) {
        std::atomic_ullong current_index(0);
        std::list<std::thread> threads;
        for (int i = 0; i < n_threads; i++) {
            threads.emplace_back(function, std::ref(current_index));
        }
        for (auto &t : threads) {
            t.join();
        }
    }

}
#endif //CONTAINERS_THREAD_POOL_H
