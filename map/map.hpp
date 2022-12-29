#ifndef __MAP_HPP__
#define __MAP_HPP__

#include <functional>
#include <memory>

#include "equal.hpp"
#include "iterator_traits.hpp"
#include "lexicographical_compare.hpp"
#include "pair.hpp"
#include "red_black_tree.hpp"

// Todo: add virtual destructor !

namespace ft {
template <class Key,                                         // map::key_type
          class T,                                           // map::mapped_type
          class Compare = std::less<Key>,                    // map::key_compare
          class Alloc = std::allocator<pair<const Key, T> >  // map::allocator_type
          >
class map {
 public:
  // member types
  class value_compare;
  typedef Key                                      key_type;
  typedef T                                        mapped_type;
  typedef ft::pair<const key_type, mapped_type>    value_type;
  typedef Compare                                  key_compare;
  typedef Alloc                                    allocator_type;
  typedef typename allocator_type::reference       reference;
  typedef typename allocator_type::const_reference const_reference;
  typedef typename allocator_type::pointer         pointer;
  typedef typename allocator_type::const_pointer   const_pointer;

 private:
  typedef RedBlackTree<value_type, value_compare, allocator_type> RBT;
  RBT                                                             tree;
  allocator_type                                                  _alloc;
  key_compare                                                     _key_comp;
  value_compare                                                   _value_comp;

 public:
  typedef typename RBT::iterator                   iterator;
  typedef typename RBT::const_iterator             const_iterator;
  typedef ft::reverse_iterator<iterator>           reverse_iterator;
  typedef ft::reverse_iterator<const_iterator>     const_reverse_iterator;
  typedef typename allocator_type::difference_type difference_type;
  typedef typename allocator_type::size_type       size_type;

 public:
  // the default constructor
  explicit map(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : tree(comp), _alloc(alloc), _key_comp(comp), _value_comp(comp) {}

  // the range constructor
  template <class InputIterator>
  map(InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : tree(comp), _alloc(alloc), _key_comp(comp), _value_comp(comp) {
    this->insert(first, last);
  }

  // the copy constructor
  map(const map& x) : tree(x.tree), _value_comp(x._value_comp) {
    this->_alloc = x._alloc;
    this->_key_comp = x._key_comp;
    this->_value_comp = x._value_comp;
  }

  // copy assignment operator
  map& operator=(const map& x) {
    if (this != &x) {
      this->tree = x.tree;
    }
    return *this;
  }

  // Iterators
  iterator       begin() { return tree.begin(); };
  const_iterator begin() const { return tree.begin(); };

  iterator       end() { return tree.end(); };
  const_iterator end() const { return tree.end(); };

  reverse_iterator       rbegin() { return reverse_iterator(this->end()); }
  const_reverse_iterator rbegin() const { return const_reverse_iterator(this->end()); }

  reverse_iterator       rend() { return reverse_iterator(this->begin()); }
  const_reverse_iterator rend() const { return const_reverse_iterator(this->begin()); }

  // Capacity
  bool      empty() const { return tree.empty(); }
  size_type size() const { return tree.size(); }
  size_type max_size() const { return tree.max_size(); };

  // Element access
  mapped_type& operator[](const key_type& k) { return (*((this->insert(ft::make_pair(k, mapped_type()))).first)).second; }

  // Modifiers

  pair<iterator, bool> insert(const value_type& val) {
    ft::pair<bool, typename RBT::pointer> ret = tree.insertUnique(val);

    return ft::pair<iterator, bool>(iterator(ret.second), ret.first);
  }

  iterator insert(iterator position, const value_type& val) {
    (void)position;  // i don't use hint in my implementation
    return this->insert(val).first;
  }

  template <class InputIterator>
  void insert(InputIterator first, InputIterator last) {
    while (first != last) {
      this->insert(*first);
      first++;
    }
  }

  void      erase(iterator position) { tree.deleteNode(*position); }
  size_type erase(const key_type& k) { return tree.deleteNode(value_type(k, mapped_type())); }
  void      erase(iterator first, iterator last) {
    while (first != last) {
      iterator tmp(first);
      tmp++;
      this->erase(first);
      first = tmp;
    }
  }

  void swap(map& x) {
    RBT tmp(x.tree);

    x.tree = this->tree;
    this->tree = tmp;
    // std::swap(this->tree, x.tree); // this would be better than above !!
  }

  void clear() { tree.clear(); }

  // Observers
  key_compare   key_comp() const { return this->_key_comp; }
  value_compare value_comp() const { return this->_value_comp; }

  // Operations

  iterator find(const key_type& k) {
    typename RBT::pointer exists = tree.find(value_type(k, mapped_type()));

    if (exists->isNil()) return this->end();

    return iterator(exists);
  }
  const_iterator find(const key_type& k) const {
    typename RBT::pointer exists = tree.find(value_type(k, mapped_type()));

    if (exists->isNil()) return this->end();

    return const_iterator(exists);
  }

  size_type count(const key_type& k) const { return this->find(k) != this->end(); }

  iterator       lower_bound(const key_type& k) { return tree.lower_bound(value_type(k, mapped_type())); }
  const_iterator lower_bound(const key_type& k) const { return tree.lower_bound(value_type(k, mapped_type())); }

  iterator       upper_bound(const key_type& k) { return tree.upper_bound(value_type(k, mapped_type())); }
  const_iterator upper_bound(const key_type& k) const { return tree.upper_bound(value_type(k, mapped_type())); }

  ft::pair<iterator, iterator>             equal_range(const key_type& k) { return ft::pair<iterator, iterator>(lower_bound(k), upper_bound(k)); }
  ft::pair<const_iterator, const_iterator> equal_range(const key_type& k) const { return ft::pair<const_iterator, const_iterator>(lower_bound(k), upper_bound(k)); }

  // Allocator
  allocator_type get_allocator() const { return this->_alloc; }

  // void test(void) const { tree.test(); } // dump the tree

  // the map destructor
  ~map() {}
};

template <class Key, class T, class Compare, class Alloc>
class map<Key, T, Compare, Alloc>::value_compare : public std::binary_function<value_type, value_type, bool> {  // in C++98, it is required to inherit binary_function<value_type,value_type,bool>
  friend class map;

 public:
  Compare comp;
  value_compare(Compare c) : comp(c) {}  // constructed with map's comparison object
 public:
  typedef bool       result_type;
  typedef value_type first_argument_type;
  typedef value_type second_argument_type;
  bool               operator()(const value_type& x, const value_type& y) const { return comp(x.first, y.first); }
};

// relational operators for map
template <class Key, class T, class Compare, class Alloc>
bool operator==(const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs) {
  return lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin());
}

template <class Key, class T, class Compare, class Alloc>
bool operator!=(const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs) {
  return !(lhs == rhs);
}

template <class Key, class T, class Compare, class Alloc>
bool operator<(const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs) {
  return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template <class Key, class T, class Compare, class Alloc>
bool operator<=(const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs) {
  return !(rhs < lhs);
}

template <class Key, class T, class Compare, class Alloc>
bool operator>(const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs) {
  return rhs < lhs;
}

}  // namespace ft

#endif