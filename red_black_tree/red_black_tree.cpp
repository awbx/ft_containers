#include "red_black_tree.hpp"
using namespace ft;

#include <iostream>
#include <map>
#include <memory>
#include <set>
#include <string>

int main() {
  RedBlackTree<std::pair<int, const char *>, std::less<std::pair<int, const char *> >, std::allocator<std::pair<const int, const char> > > tree;

  tree.insert(std::pair<int, const char *>(0, "awbx1"));
  for(size_t idx =0; idx < 20; idx++)
  {
    int value = rand() % 500;
    tree.insert(std::pair<int, const char *>(idx & 1? -value: value, "awbx1"));

  }

  tree.dump_dot();

  // std::cout << "tree.empty() = " << tree.empty() << std::endl;
  // std::cout << "tree.size() = " << tree.size() << std::endl;
  // std::cout << "tree.max_size() = " << tree.max_size() << std::endl;
}