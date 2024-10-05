cmake_minimum_required(VERSION 3.26)
project(fundamental_algorithms C)

set(CMAKE_C_STANDARD 11)

add_executable(lab1t1 lab1/task1/main.c lab1/task1/handlers.c lab1/task1/main.h lab1/arrays/array.h
        lab1/error_handler.c
        lab1/error_handler.h)
add_executable(lab1t2 lab1/task2/main.c lab1/task2/main.h
        lab1/task2/methods.c
        lab1/task2/expressions.c
        lab1/error_handler.c
        lab1/error_handler.h)
add_executable(lab1t3
        lab1/task3/main.c
        lab1/task3/main.h
        lab1/task3/handlers.c
        lab1/error_handler.c
        lab1/error_handler.h)
add_executable(lab1t4 lab1/task4/main.c lab1/task4/main.h
        lab1/task4/handlers.c
        lab1/error_handler.c
        lab1/error_handler.h)
add_executable(lab1t7 lab1/task7/main.c lab1/task7/main.h
        lab1/error_handler.c
        lab1/error_handler.h
        lab1/task7/handlers.c
        lab1/arrays/array.c
        lab1/arrays/array.h)
add_executable(lab1t5 lab1/task5/main.c lab1/task5/main.h
        lab1/task5/methods.c
        lab1/error_handler.c
        lab1/error_handler.h)
add_executable(lab1t6 lab1/task6/main.c lab1/task6/main.h
        lab1/task6/methods.c
        lab1/error_handler.c
        lab1/error_handler.h)
add_executable(lab1t8 lab1/task8/main.c lab1/task8/main.h
        lab1/arrays/array.c
        lab1/arrays/array.h
        lab1/error_handler.c
        lab1/error_handler.h
        lab1/task8/handlers.c)
add_executable(lab1t9 lab1/task9/main.c lab1/task9/main.h
        lab1/arrays/intarray.c
        lab1/arrays/intarray.h
        lab1/error_handler.c
        lab1/error_handler.h
        lab1/task9/handlers.c)

target_link_libraries(lab1t1 m)
target_link_libraries(lab1t2 m)
target_link_libraries(lab1t3 m)
target_link_libraries(lab1t4 m)
target_link_libraries(lab1t6 m)
