#include "tests.hpp"

void start_test(const char *test_name, void (*func)(void)) {
    std::cout << "------------------- " << test_name << "        -------------------\n";
    func();
    std::cout << "------------------- End Of " << test_name << " -------------------\n";
}

int main() { stack_main(); }