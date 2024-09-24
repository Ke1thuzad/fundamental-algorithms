cmake_minimum_required(VERSION 3.26)
project(fundamental_algorithms C)

set(CMAKE_C_STANDARD 11)

add_executable(lab1t1 lab1/task1/main.c lab1/task1/handlers.c lab1/task1/main.h lab1/task1/array.h)
add_executable(lab1t2 lab1/task2/main.c lab1/task2/main.h
        lab1/task2/methods.c
        lab1/task2/expressions.c)
add_executable(lab1t3
        lab1/task3/main.c
        lab1/task3/main.h
        lab1/task3/handlers.c)

target_link_libraries(lab1t1 m)
target_link_libraries(lab1t2 m)