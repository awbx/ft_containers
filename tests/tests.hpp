#ifndef __TESTS_HPP__
#define __TESTS_HPP__

#include <deque>     // std::deque
#include <iomanip>   // std::setw
#include <iostream>  // std::cout
#include <stack>     // std::stack
#include <vector>    // std::vector

#if FT
namespace ft = std;
#else
#include "stack.hpp"  // ft::stack

#endif

void start_test(const char *test_name, void (*func)(void));

void stack_main(void);
void vector_main(void);

#endif