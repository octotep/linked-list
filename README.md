# Linked List in C++

Good exercise to demonstrate C++ pointer management and testing capability!

Other nice things about this implementation:

- Generic implementation which demonstrates understanding of templates
- Iterators to enable forwards and reverse iteration and modern C++ syntax sugar `for (auto& thing : list)`
- Demonstrates move semantics

## Testing

The source file main.cpp is compiled into `linked_list`. This is a short program which demonstrates how to use the class.

Catch unit tests found in test.cpp and compiled into `linked_list_test`. They are all registered with CTest, so one can use ctest instead of running the executable direcctly to see all tests pass.

```
mkdir build
cd build
cmake ..
cmake --build . -j
ctest
```

Example output:

```
Test project /home/octotep/projects/linked-list/build
    Start 1: Create a linked list and insert one element in it
1/9 Test #1: Create a linked list and insert one element in it ........................   Passed    0.01 sec
    Start 2: Create a linked list and emplace one element in it
2/9 Test #2: Create a linked list and emplace one element in it .......................   Passed    0.01 sec
    Start 3: Create a linked list and emplace two elements into it at the beginning
3/9 Test #3: Create a linked list and emplace two elements into it at the beginning ...   Passed    0.01 sec
    Start 4: Create a linked list and insert into the middle
4/9 Test #4: Create a linked list and insert into the middle ..........................   Passed    0.01 sec
    Start 5: Create a linked list and insert at the end
5/9 Test #5: Create a linked list and insert at the end ...............................   Passed    0.01 sec
    Start 6: Iterate forwards
6/9 Test #6: Iterate forwards .........................................................   Passed    0.01 sec
    Start 7: Iterate backwards
7/9 Test #7: Iterate backwards ........................................................   Passed    0.01 sec
    Start 8: Forwards cursor
8/9 Test #8: Forwards cursor ..........................................................   Passed    0.01 sec
    Start 9: Backwards cursor
9/9 Test #9: Backwards cursor .........................................................   Passed    0.01 sec

100% tests passed, 0 tests failed out of 9

Total Test time (real) =   0.06 sec
```
