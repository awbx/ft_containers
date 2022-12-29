#include "tests.hpp"

void start_test(const char *test_name, void (*func)(void)) {
  std::cout << "------------------- " << test_name << "        -------------------\n";
  func();
  std::cout << "------------------- End Of " << test_name << " -------------------\n";
}

int main() {
  std::cout << "------------------- Start Of vector Tests -------------------\n";
  vector_main();
  std::cout << "------------------- Start Of stack Tests -------------------\n";
  stack_main();
  std::cout << "------------------- Start Of map Tests -------------------\n";
  map_main();
  std::cout << "------------------- Start Of set Tests -------------------\n";
  set_main();
}