cmake_minimum_required(VERSION 3.26)
project(fundamental_algorithms C)

set(CMAKE_C_STANDARD 11)

file(GLOB utility/*.h utility/*.c)

add_executable(lab1t1 lab1/task1/main.c lab1/task1/handlers.c lab1/task1/main.h
        utility/error_handler.c
        utility/error_handler.h)
add_executable(lab1t2 lab1/task2/main.c lab1/task2/main.h
        lab1/task2/methods.c
        lab1/task2/expressions.c
        utility/error_handler.c
        utility/error_handler.h)
add_executable(lab1t3
        lab1/task3/main.c
        lab1/task3/main.h
        lab1/task3/handlers.c
        utility/error_handler.c
        utility/error_handler.h)
add_executable(lab1t4 lab1/task4/main.c lab1/task4/main.h
        lab1/task4/handlers.c
        utility/error_handler.c
        utility/error_handler.h)
add_executable(lab1t7 lab1/task7/main.c lab1/task7/main.h
        utility/error_handler.c
        utility/error_handler.h
        lab1/task7/handlers.c
        utility/arrays/array.c
        utility/arrays/array.h)
add_executable(lab1t5 lab1/task5/main.c lab1/task5/main.h
        lab1/task5/methods.c
        utility/error_handler.c
        utility/error_handler.h)
add_executable(lab1t6 lab1/task6/main.c lab1/task6/main.h
        lab1/task6/methods.c
        utility/error_handler.c
        utility/error_handler.h)
add_executable(lab1t8 lab1/task8/main.c lab1/task8/main.h
        utility/arrays/array.c
        utility/arrays/array.h
        utility/error_handler.c
        utility/error_handler.h
        lab1/task8/handlers.c)
add_executable(lab1t9 lab1/task9/main.c lab1/task9/main.h
        utility/arrays/intarray.c
        utility/arrays/intarray.h
        utility/error_handler.c
        utility/error_handler.h
        lab1/task9/handlers.c)
add_executable(lab1t10 lab1/task10/main.c lab1/task10/main.h
        lab1/task10/handlers.c
        utility/arrays/array.c
        utility/arrays/array.h
        utility/error_handler.c
        utility/error_handler.h)
add_executable(lab2t1 lab2/task1/main.c lab2/task1/main.h
        lab2/task1/handlers.c
        utility/arrays/array.c
        utility/arrays/array.h
        utility/error_handler.c
        utility/error_handler.h)

add_executable(lab2t2 lab2/task2/main.c lab2/task2/main.h
        lab2/task2/handlers.c
        utility/error_handler.h
        utility/error_handler.c)

add_executable(lab2t3 lab2/task3/main.c lab2/task3/main.h
        lab2/task3/handlers.c
        utility/error_handler.h
        utility/error_handler.c)

add_executable(lab2t4 lab2/task4/main.c lab2/task4/main.h
        lab2/task4/handlers.c
        utility/arrays/array.c
        utility/arrays/array.h
        utility/error_handler.h
        utility/error_handler.c)

add_executable(lab2t7 lab2/task7/main.c lab2/task7/main.h
        lab2/task7/expressions.c
        utility/error_handler.h
        utility/error_handler.c)

add_executable(lab2t8 lab2/task8/main.c lab2/task8/main.h
        utility/arrays/array.c
        utility/arrays/array.h
        utility/error_handler.c
        utility/error_handler.h)

add_executable(lab2t5 lab2/task5/main.c lab2/task5/main.h
        lab2/task5/handlers.c
        utility/arrays/array.c
        utility/arrays/array.h
        utility/arrays/intarray.c
        utility/arrays/intarray.h
        utility/error_handler.c
        utility/error_handler.h)

add_executable(lab2t9 lab2/task9/main.c lab2/task9/main.h
        utility/error_handler.c
        utility/error_handler.h
        utility/arrays/intarray.c
        utility/arrays/intarray.h)

add_executable(lab2t6 lab2/task6/main.c lab2/task6/main.h
        utility/error_handler.c
        utility/error_handler.h
        utility/arrays/array.c
        utility/arrays/array.h
        lab2/task6/handlers.c)
add_executable(lab2t10 lab2/task10/main.c
        lab2/task10/main.h
        utility/error_handler.c
        utility/error_handler.h
        utility/arrays/intarray.c
        utility/arrays/intarray.h)


add_executable(lab3t3 lab3/task3/main.c lab3/task3/main.h
        utility/error_handler.c
        utility/error_handler.h
        utility/arrays/array.c
        utility/arrays/array.h)

add_executable(lab3t1 lab3/task1/main.c lab3/task1/main.h
        utility/error_handler.c
        utility/error_handler.h)

add_executable(lab3t4 lab3/task4/main.c lab3/task4/main.h
        lab3/task4/mystring.c
        utility/error_handler.c
        utility/error_handler.h
        lab3/task4/mystring.h
        lab3/task4/mail.c
        lab3/task4/mail.h
        utility/arrays/array.c
        utility/arrays/array.h
        utility/overio.c
        utility/overio.h
        lab3/task4/dialog.c)

add_executable(lab3t5 lab3/task5/main.c lab3/task5/main.h
        lab3/task5/handlers.c
        utility/overio.c
        utility/overio.h
        utility/error_handler.c
        utility/error_handler.h
        utility/arrays/array.c
        utility/arrays/array.h
        lab3/task5/student.c
        lab3/task5/handlers.c
        lab3/task5/dialog.c)

add_executable(lab3t2 lab3/task2/main.c lab3/task2/main.h
        lab3/task2/vectorarray.c
        utility/error_handler.c
        utility/error_handler.h)
add_executable(lab3t6 lab3/task6/main.c lab3/task6/main.h
        utility/error_handler.c
        utility/error_handler.h)
add_executable(lab3t8 lab3/task8/main.c lab3/task8/main.h
        lab3/task8/polynomial.c
        utility/error_handler.c
        utility/error_handler.h
        lab3/task8/adder.c
        utility/arrays/array.c
        utility/arrays/array.h
        utility/overio.c
        utility/overio.h)

add_executable(lab3t10 lab3/task10/main.c lab3/task10/main.h
        utility/error_handler.c
        utility/error_handler.h
        utility/arrays/array.c
        utility/arrays/array.h
        utility/overio.c
        utility/overio.h)

add_executable(lab3t7 lab3/task7/main.c lab3/task7/main.h
        lab3/task7/list.c
        lab3/task7/dialog.c
        lab3/task7/stack.c
        utility/error_handler.c
        utility/error_handler.h
        utility/arrays/array.c
        utility/arrays/array.h
        utility/overio.c
        utility/overio.h
        lab3/task4/mystring.c
        lab3/task4/mystring.h)

add_executable(lab3t9 lab3/task9/main.c lab3/task9/main.h
        lab3/task9/tree.c
        lab3/task4/mystring.c
        lab3/task4/mystring.h
        utility/error_handler.c
        utility/error_handler.h
        lab3/task9/list.c
        lab3/task9/dialog.c
        utility/arrays/array.c
        utility/arrays/array.h
        utility/overio.c
        utility/overio.h)

add_executable(lab4t1 lab4/task1/main.c lab4/task1/main.h
        lab4/task1/structures.c
        lab3/task4/mystring.c
        lab3/task4/mystring.h
        utility/error_handler.c
        utility/error_handler.h
        utility/arrays/array.c
        utility/arrays/array.h)

add_executable(lab4t9 lab4/task9/main.c lab4/task9/main.h
        lab4/task9/heaps.h
        lab4/task9/heaps.c
        utility/error_handler.c
        utility/error_handler.h
        lab4/task9/heaps/binomial/binomial.c
        lab4/task9/heaps/binomial/binomial.h
        lab4/task9/heaps/fibonacci/fibonacci.c
        lab4/task9/heaps/fibonacci/fibonacci.h
        lab4/task9/support_app.c
        lab4/task9/support_app.h
        lab4/task9/heaps/binary/binary.c
        lab4/task9/heaps/binary/binary.h
        lab4/task9/heaps/leftist/leftist.c
        lab4/task9/heaps/leftist/leftist.h
        lab4/task9/heaps/skew/skew.c
        lab4/task9/heaps/skew/skew.h
        lab4/task9/heaps/treap/treap.c
        lab4/task9/heaps/treap/treap.h
        lab3/task4/mystring.c
        lab3/task4/mystring.h
        lab4/task9/department_structures/bst/bst.c
        lab4/task9/department_structures/bst/bst.h
        lab4/task9/department_structures/dynamic_array/dynamic_array.c
        lab4/task9/department_structures/dynamic_array/dynamic_array.h
        lab4/task9/department_structures/hashset/hashset.c
        lab4/task9/department_structures/hashset/hashset.h
        lab4/task9/department_structures/trie/trie.c
        lab4/task9/department_structures/trie/trie.h
        lab4/task9/department_structures/department.c
        lab4/task9/department_structures/department.h
        lab4/task9/ticket.h
        lab4/task9/department_structures/department_structure.h
        lab4/task9/department_structures/overload_heap/overload_heap.c
        lab4/task9/department_structures/overload_heap/overload_heap.h)

target_link_libraries(lab1t1 m)
target_link_libraries(lab1t2 m)
target_link_libraries(lab1t3 m)
target_link_libraries(lab1t4 m)
target_link_libraries(lab1t6 m)
target_link_libraries(lab2t2 m)
target_link_libraries(lab2t9 m)
target_link_libraries(lab2t10 m)
target_link_libraries(lab3t3 m)
target_link_libraries(lab3t2 m)
target_link_libraries(lab4t9 m)
