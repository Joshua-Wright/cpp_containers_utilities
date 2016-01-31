cmake_minimum_required(VERSION 3.3)
project(containers)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++14")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lfltk -lfltk_images")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lpthread")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -g")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g3")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lginac -lcln") # for ginac
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lboost_timer -lboost_system")

add_executable(containers tests/test_llong_tree.cpp lib/llong_tree.cpp tests/test_thread_pool.cpp tests/test_thread_pool.h)

add_executable(fill_tree
        lib/llong_tree.cpp
        lib/array_tree.cpp
        tests/fill_tree.cpp
        lib/getRSS.c)

add_executable(test_array_tree
        lib/array_tree.cpp
        tests/test_array_tree.cpp)

add_executable(test_dynamic_array
        tests/test_dynamic_array.cpp
        )

add_executable(test_matrix
        tests/test_matrix.cpp
        )

add_executable(test_thread_pool
        lib/thread_pool.h
        tests/test_thread_pool.cpp
        tests/test_thread_pool.h)

add_executable(test_stack
        lib/stack.h
        tests/test_stack.cpp
        )

add_executable(bench_stdlib_vector_vs_list
        tests/bench_stdlib_vector_vs_list.cpp
        )

add_executable(fast_random
        util/fast_random.cpp
        )


add_executable(test_pi_speed
        tests/test_pi_speed.cpp)


add_executable(test_double_linked_list lib/double_linked_list.h tests/test_double_linked_list.cpp)