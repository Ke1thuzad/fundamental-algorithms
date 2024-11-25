cmake_minimum_required(VERSION 3.26)
project(fundamental_algorithms CXX)

set(CMAKE_CXX_STANDARD 23)

add_executable(lab5t1 task1/main.cpp task1/main.h
        task1/classes.cpp)
add_executable(lab5t2 task2/main.cpp task2/main.h
        task2/encoder.cpp)
