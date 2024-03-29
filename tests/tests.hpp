#ifndef __TESTS_HPP__
#define __TESTS_HPP__

#include <deque>     // std::deque
#include <iostream>  // std::cout
#include <map>       // std::map
#include <stack>     // std::stack
#include <vector>    // std::vector
#include <set>

#if STD
namespace ft = std;
#elif FT
#include "map.hpp"
#include "set.hpp"
#include "stack.hpp"  // ft::stack
#include "vector.hpp"

#endif

void start_test(const char *test_name, void (*func)(void));

void stack_main(void);
void vector_main(void);
void map_main(void);
void set_main(void);

#endif
