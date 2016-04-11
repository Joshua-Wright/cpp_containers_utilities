cmake_minimum_required(VERSION 3.3)
project(containers)

# for using clang
#set(CMAKE_C_COMPILER   "/usr/bin/clang")
#set(CMAKE_CXX_COMPILER "/usr/bin/clang++")

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Ilib/")
include_directories(lib/)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++14")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lpthread -fopenmp")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O1")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g3")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ffast-math")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lginac -lcln") # for ginac
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lboost_timer -lboost_system")

add_executable(test_dynamic_array
        tests/test_dynamic_array.cpp
        )

add_executable(test_matrix
        tests/test_matrix.cpp
        lib/matrix.h
        )

add_executable(test_vect
        tests/test_vect.cpp
        lib/vect.h
        )

add_executable(test_thread_pool
        lib/thread_pool.h
        tests/test_thread_pool.cpp
        tests/test_thread_pool.h)

add_executable(test_stack
        lib/stack.h
        tests/test_stack.cpp
        )

add_executable(fast_random
        util/fast_random.cpp
        )


add_executable(test_double_linked_list lib/double_linked_list.h tests/test_double_linked_list.cpp)

add_executable(test_single_linked_list lib/single_linked_list.h tests/test_single_linked_list.cpp)

add_executable(test_binary_search_tree lib/binary_search_tree.h tests/test_binary_search_tree.cpp)

add_executable(test_array_list tests/test_array_list.cpp lib/array_list.h)

add_executable(test_debug tests/test_debug.cpp)

add_executable(test_arg_parser tests/test_arg_parser.cpp lib/arg_parser.cpp lib/arg_parser.h)

add_executable(test_mergesort tests/test_mergesort.cpp)
add_executable(test_quicksort "tests/benchmark_sorts.cpp")