#ifndef __SET_HPP__
#define __SET_HPP__

#include <functional>
#include <memory>

#include "iterator_traits.hpp"
#include "pair.hpp"
#include "red_black_tree.hpp"

namespace ft {

template <class T,                    // set::key_type/value_type
          class Compare = less<T>,    // set::key_compare/value_compare
          class Alloc = allocator<T>  // set::allocator_type
          >
class set {
 public:
  // member types
  typedef T                                                       key_type;
  typedef T                                                       value_type;
  typedef Compare                                                 key_compare;
  typedef Compare                                                 value_compare;
  typedef Alloc                                                   allocator_type;
  typedef typename allocator_type::reference                      reference;
  typedef typename allocator_type::const_reference                const_reference;
  typedef typename allocator_type::pointer                        pointer;
  typedef typename allocator_type::const_pointer                  const_pointer;
  typedef RedBlackTree<value_type, value_compare, allocator_type> RBT;
  typedef typename RBT::iterator                                  iterator;
  typedef typename RBT::const_iterator                            const_iterator;
  typedef ft::reverse_iterator<iterator>                          reverse_iterator;
  typedef ft::reverse_iterator<const_iterator>                    const_reverse_iterator;
  typedef typename allocator_type::difference_type                difference_type;
  typedef typename allocator_type::size_type                      size_type;

 private:
  RBT tree;

  allocator_type _alloc;
  key_compare    _key_comp;
  value_compare  _value_comp;

 public:
  // the default constructor
  explicit set(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : tree(comp), _alloc(alloc), _key_comp(comp), _value_comp(comp) {}

  // the range constructor
  template <class InputIterator>
  set(InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : tree(comp), _alloc(alloc), _key_comp(comp), _value_comp(comp) {
    this->insert(first, last);
  }

  // the copy constructor
  set(const set& x) : tree(x.tree) {
    this->_alloc = x._alloc;
    this->_key_comp = x._key_comp;
    this->_value_comp = x._value_comp;
  }

  // copy assignment operator
  set& operator=(const set& x) {
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
  size_type erase(const key_type& k) { return tree.deleteNode(k); }
  void      erase(iterator first, iterator last) {
    while (first != last) {
      iterator tmp(first);
      tmp++;
      this->erase(first);
      first = tmp;
    }
  }

  void swap(set& x) {
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
    typename RBT::pointer exists = tree.find(k);

    if (exists->isNil()) return this->end();

    return iterator(exists);
  }
  const_iterator find(const key_type& k) const {
    typename RBT::pointer exists = tree.find(k);

    if (exists->isNil()) return this->end();

    return const_iterator(exists);
  }

  size_type count(const key_type& k) const { return this->find(k) != this->end(); }

  iterator       lower_bound(const key_type& k) { return tree.lower_bound(k); }
  const_iterator lower_bound(const key_type& k) const { return tree.lower_bound(k); }

  iterator       upper_bound(const key_type& k) { return tree.upper_bound(k); }
  const_iterator upper_bound(const key_type& k) const { return tree.upper_bound(k); }

  ft::pair<iterator, iterator>             equal_range(const key_type& k) { return ft::pair<iterator, iterator>(lower_bound(k), upper_bound(k)); }
  ft::pair<const_iterator, const_iterator> equal_range(const key_type& k) const { return ft::pair<const_iterator, const_iterator>(lower_bound(k), upper_bound(k)); }

  // Allocator
  allocator_type get_allocator() const { return this->_alloc; }

  // void test(void) const { tree.test(); }  // dump the tree

  // the set destructor
  ~set() {}
};

}  // namespace ft

#endif