#ifndef __RBT_ITERATOR_HPP__
#define __RBT_ITERATOR_HPP__

#include "iterator.hpp"

namespace ft {

template <typename T>
class tree_iterator : ft::iterator<ft::bidirectional_iterator_tag, typename T::value_type> {
  T* node;

 public:
  typedef typename T::value_type                                                               value_type;
  typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::iterator_category iterator_category;
  typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::difference_type   difference_type;
  typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::pointer           pointer;
  typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::reference         reference;

  tree_iterator() : node(nullptr){};

  tree_iterator(T* _node) : node(_node) {}

  tree_iterator(const tree_iterator& copy) : node(copy.node) {}

  virtual ~tree_iterator() {}

  tree_iterator& operator=(const tree_iterator& rhs) {
    if (*this != rhs) {
      this->node = rhs.node;
    }
    return (*this);
  }

  bool operator==(const tree_iterator& rhs) const { return (this->node == rhs.node); }

  bool operator!=(const tree_iterator& rhs) const { return (this->node != rhs.node); }

  reference operator*() const { return (reference)(this->node->data); }

  pointer operator->() const { return (pointer)(&this->node->data); }

  tree_iterator& operator++(void) {
    this->node = T::getSuccessor(this->node);
    return (*this);
  }

  tree_iterator operator++(int) {
    tree_iterator tmp(*this);
    ++(*this);
    return (tmp);
  }

  tree_iterator& operator--(void) {
    this->node = T::getPredecessor(this->node);
    return (*this);
  }

  tree_iterator operator--(int) {
    tree_iterator tmp(*this);
    --(*this);
    return (tmp);
  }
};

}  // namespace ft

#endif