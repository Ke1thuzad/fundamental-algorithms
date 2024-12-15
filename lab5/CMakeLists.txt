cmake_minimum_required(VERSION 3.26)
project(fundamental_algorithms CXX)

set(CMAKE_CXX_STANDARD 23)

add_executable(lab5t1 task1/main.cpp task1/main.h
        task1/classes.cpp)
add_executable(lab5t2 task2/main.cpp task2/main.h
        task2/encoder.cpp)
add_executable(lab5t4 task4/main.cpp task4/main.h
        task4/complex.cpp)
add_executable(lab5t3 task3/main.cpp task3/main.h
        task3/classes.cpp)
add_executable(lab5t6 task6/main.cpp task6/main.h
        task6/classes.cpp)
add_executable(lab5t7 task7/main.cpp task7/main.h
        task7/classes.cpp)
