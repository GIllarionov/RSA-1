cmake_minimum_required(VERSION 3.21)
project(RSA_1)

set(CMAKE_CXX_STANDARD 23)

add_executable(RSA_1 main.cpp math.hpp)
add_executable(RSA_2 math.hpp test.cpp doctest.cpp)

enable_testing()
add_test(NAME TESTS COMMAND RSA_2)