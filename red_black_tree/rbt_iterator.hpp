#ifndef __RBT_ITERATOR_HPP__
#define __RBT_ITERATOR_HPP__

#include "iterator.hpp"
#include "red_black_tree.hpp"

namespace ft {

template <typename T>
class Node;

template <typename T>
class tree_iterator : public ft::iterator<ft::bidirectional_iterator_tag, T> {
 private:
  typedef T *ptr;

 public:
  typedef typename ft::iterator_traits<ptr>::value_type      value_type;
  typedef typename ft::iterator_traits<ptr>::difference_type difference_type;
  typedef typename ft::iterator_traits<ptr>::pointer         pointer;
  typedef typename ft::iterator_traits<ptr>::reference       reference;
  // Todo: add category type

 private:
  typedef ft::Node<T>        node_type;
  typedef node_type         *node_pointer;
  typedef const node_pointer const_node_pointer;
  node_pointer               tree;

  // private member functions
  node_pointer base() const { return this->tree; }

 public:
  // member functions

  tree_iterator() : tree(nullptr) {}

  explicit tree_iterator(const_node_pointer root) : tree(root){};

  tree_iterator(tree_iterator const &vector_iter) : tree(vector_iter.base()) {}

  tree_iterator operator=(tree_iterator const &rhs) {
    if (this != &rhs) {
      this->tree = rhs.base();
    }
    return *this;
  }

  reference operator*() const { return tree->data; }

  tree_iterator &operator++() {
    this->tree = node_type::getSuccessor(this->tree);
    return *this;
  }

  tree_iterator operator++(int) {
    tree_iterator tmp = *this;
    ++(*this);
    return tmp;
  }

  tree_iterator &operator--() {
    this->tree = node_type::getPredecessor(this->tree);
    return *this;
  }

  tree_iterator operator--(int) {
    tree_iterator tmp = *this;
    --(*this);
    return tmp;
  }

  pointer operator->() const { return &this->tree->data; }

  // relational operators

  bool operator==(const tree_iterator &rhs) { return this->base() == rhs.base(); }
  bool operator!=(const tree_iterator &rhs) { return this->base() != rhs.base(); }
};

}  // namespace ft

#endif