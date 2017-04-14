cmake_minimum_required(VERSION 3.3)
project(containers)

# for using clang
# set(CMAKE_C_COMPILER   "/usr/bin/clang")
# set(CMAKE_CXX_COMPILER "/usr/bin/clang++")

include_directories(include/)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++14")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O1")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g3")

add_executable(test_debug          tests/test_debug.cpp)
add_executable(test_matrix         tests/test_matrix.cpp)
add_executable(test_vect           tests/test_vect.cpp)
add_executable(test_arg_parser     tests/test_arg_parser.cpp     src/arg_parser.cpp)
add_executable(test_reflect_v2     tests/test_reflect_v2.cpp)


add_library(arg_parser STATIC src/arg_parser.cpp)
export(TARGETS arg_parser FILE arg_parser.cmake)
target_include_directories(arg_parser PUBLIC include/)

add_library(cubic_interp STATIC src/cubic_interp.cpp)
export(TARGETS cubic_interp FILE cubic_interp.cmake)
target_include_directories(cubic_interp PUBLIC include/)
