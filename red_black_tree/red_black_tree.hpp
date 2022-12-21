#ifndef __RED_BLACK_TREE_HPP__
#define __RED_BLACK_TREE_HPP__

// let's assume that the true value is red & false value is black

#define red true
#define black false
#define nil 0

#define IsRed(x) ((x) && (x)->color == true)
#define IsBlack(x) (!IsRed(x))
#define IsRoot(x) ((x) && (x)->parent == nil)
#define IsNil(x) ((x) == nil)
#define IsLeftChild(x) (!IsNil(x) && (x)->parent && x == (x)->parent->left)
#define IsRightChild(x) (!IsNil(x) && (x)->parent && x == (x)->parent->right)
#define IsChildrenRed(x) (!IsNil(x) && (IsNil(x->left) || IsBlack(x->left)) && (IsNil(x->right) || IsBlack(x->right)))
#define GetParent(x) (!IsNil(x) && !IsNil(x->parent) ? x->parent : nil)
#define GetGrandParent(x) (GetParent(GetParent(x)))
#define GetUncle(x) (GetGrandParent(x) ? (IsLeftChild(GetParent(x)) ? GetGrandParent(x)->right : GetGrandParent(x)->left) : nil)

#define ReColor(x) ((x)->color ^= 1);

#include <iomanip>
#include <iostream>

#include "rbt_iterator.hpp"
#include "reverse_iterator.hpp"

namespace ft {

template <class T>
class Node {
 public:
  typedef T                 value_type;
  typedef Node<value_type> *pointer;

  // members;
  T       data;
  pointer left;
  pointer right;
  pointer parent;
  bool    color;

  Node(const T &data, pointer parent = nil, bool color = true) : data(data), left(nil), right(nil), parent(parent), color(color) {}

  static pointer getMinimum(const pointer tree) {
    pointer min = tree;

    while (min && min->left) {
      min = min->left;
    }
    return min;
  }

  static pointer getMaximum(const pointer tree) {
    pointer max = tree;

    while (max && max->right) {
      max = max->right;
    }
    return max;
  }

    static pointer getSuccessor(pointer x) {
    if (IsNil(x))
      return (x);
    else if (x->right != nil)
      return getMinimum(x->right);
    pointer y = x->parent;
    while (y != nil && y->right == x) {
      x = y;
      y = y->parent;
    }
    return y;
  }

  static pointer getPredecessor(pointer x) {
    if (IsNil(x))
      return x;
    else if (x->left != nil)
      return getMaximum(x->left);

    pointer y = x->parent;

    while (y != nil && y->left == x) {
      x = y;
      y = y->parent;
    }
    return y;
  }

  static pointer find(const pointer tree, const value_type &val) {
    pointer tmp = tree;

    while (tmp) {
      if (tmp->data == val)
        return tmp;
      else if (val > tmp->data)
        tmp = tmp->right;
      else
        tmp = tmp->left;
    }

    return tmp;
  }

  static void label(pointer node, int &id) {
    std::cout << "\tNode" << id << "[label=\"" << (node ? std::to_string(node->data) : "NIL") << "\""
              << ", fillcolor=\"" << (IsRed(node) ? "red" : "black") << "\""
              << ", color=\"black\""
              << ", shape=" << (IsNil(node) ? "record" : "circle") << ", fixedsize=true"
              << ", fontcolor=\"white\""
              << ", tooltip=\"The parent node is " << (node && node->parent ? std::to_string(node->parent->data) : "nil") << "\""
              << ", style=filled" << ((IsNil(node)) ? ", width=0.3, height=0.2, fontsize=10" : ", fontsize=20") << "]\n";
  }

  static void edge(int from, int to) {
    std::cout << "\tNode" << from << " -> "
              << "Node" << to << "[wieght=10]\n";
  }

  static int dfs(pointer tree, int &id) {
    int my_id, l, r;
    my_id = id++;
    label(tree, my_id);
    if (tree) {
      l = dfs(tree->left, id);
      r = dfs(tree->right, id);
      edge(my_id, l);
      edge(my_id, r);
    }
    return my_id;
  }
  
  static void dump_dot(pointer tree) {
    int id = 1;
    std::cout << "digraph {\n";
    dfs(tree, id);
    std::cout << "}\n";
  }
};

template <typename T, typename Compare, typename Alloc>
class RedBlackTree {
 public:
  // member types
  typedef T                                                          value_type;
  typedef Node<value_type>                                           node_type;
  typedef Compare                                                    key_compare;
  typedef Alloc                                                      allocator_type;
  typedef typename allocator_type::template rebind<node_type>::other node_alloc;
  typedef RedBlackTree<value_type, key_compare, node_alloc>          tree;
  typedef typename node_alloc::reference                             reference;
  typedef typename node_alloc::const_reference                       const_reference;
  typedef typename node_alloc::pointer                               pointer;
  typedef typename node_alloc::const_pointer                         const_pointer;
  typedef ft::tree_iterator<value_type>                              iterator;
  typedef ft::tree_iterator<const value_type>                        const_iterator;
  typedef ft::reverse_iterator<iterator>                             reverse_iterator;
  typedef ft::reverse_iterator<const_iterator>                       const_reverse_iterator;
  typedef typename node_alloc::difference_type                       difference_type;
  typedef typename node_alloc::size_type                             size_type;

 private:
  pointer     _root;
  size_type   _size;
  node_alloc  _alloc;
  key_compare _comp;

  pointer _end;

 public:
  // The default constructor creates an empty container, with no elements.
  RedBlackTree() : _root(nil), _size(0) {
    this->_end = this->_alloc.allocate(1);
    this->_alloc.construct(this->_end, value_type());
  };

  // capacity functions
  bool      empty() const { return !this->size(); }
  size_type size() const { return this->_size; }
  size_type max_size() const { return this->_alloc.max_size(); }

  allocator_type get_allocator() const { return this->_alloc; }

  ~RedBlackTree() {
    // TODO: deallocate all nodes
    this->_alloc.destroy(this->_end);
    this->_alloc.deallocate(this->_end, 1);
    this->clean(this->_root);
  };

  void clean(pointer node) {
    if (IsNil(node)) return;

    pointer left = node->left;
    pointer right = node->right;
    this->_alloc.destroy(node);
    this->_alloc.deallocate(node, 1);
    clean(left);
    clean(right);
  }
  // set & unset the _end
  void set_end(void) {
    if (!IsNil(this->_root)) {
      this->_root->parent = this->_end;
      this->_end->left = this->_root;
    }
  }

  void unset_end(void) {
    if (!IsNil(this->_root)) {
      _root->parent = nil;
      this->_end->left = nil;
    }
  }

  // iterator

  iterator       begin() { return iterator(this->size() ? this->getMinimum() : this->_end); }
  const_iterator begin() const { return iterator(this->size() ? this->getMinimum() : this->_end); }

  iterator       end() { return iterator(this->_end); }
  const_iterator end() const { return iterator(this->_end); }

  reverse_iterator       rbegin() { return reverse_iterator(this->end()); }
  const_reverse_iterator rbegin() const { return reverse_iterator(this->end()); }

  reverse_iterator       rend() { return reverse_iterator(this->begin()); }
  const_reverse_iterator rend() const { return reverse_iterator(this->begin()); }

  // red black tree functions

  pointer insert(const value_type &val) {
    pointer z = this->_alloc.allocate(1);
    this->_alloc.construct(z, val);

    pointer y = nil;
    pointer x = this->_root;

    // find the right position to put z
    while (!IsNil(x)) {
      y = x;  // track the parent
      if (this->_comp(z->data, x->data))
        x = x->left;
      else
        x = x->right;
    }

    if (IsNil(y))
      this->_root = z;
    else if (this->_comp(z->data, y->data))
      y->left = z;
    else
      y->right = z;

    // set z parent
    z->parent = y;

    this->insertFixUp(z);
    // increase the size of tree
    this->_size++;
    return z;
  }
  void insertFixUp(pointer z) {
    while (IsRed(GetParent(z))) {
      pointer uncle = GetUncle(z);

      if (IsRed(uncle)) {  // start of case 1
        ReColor(GetParent(z));
        ReColor(GetGrandParent(z));
        ReColor(uncle);
        z = GetGrandParent(z);                                    // end of case 1
      } else if (IsRightChild(z) && IsLeftChild(GetParent(z))) {  // start of case 2
        z = GetParent(z);
        this->leftRotate(z);
      } else if (IsLeftChild(z) && IsRightChild(GetParent(z))) {
        z = GetParent(z);
        this->rightRotate(z);  // end of case 2
      } else {
        ReColor(GetParent(z));  // start of case 3
        ReColor(GetGrandParent(z));
        if (IsLeftChild(GetParent(z)))
          this->rightRotate(GetGrandParent(z));
        else
          this->leftRotate(GetGrandParent(z));  // end of case 3
      }
    }
    this->_root->color = black;
  };

  // find
  pointer find(const value_type &val) { return node_type::find(this->_root, val); }

  pointer getMinimum(void) const { return node_type::getMinimum(this->_root); }

  pointer getMaximum(void) const { return node_type::getMaximum(this->_root); }

  pointer leftRotate(pointer x) {
    if (IsNil(x) || IsNil(x->right)) return nil;
    pointer y = x->right;
    x->right = y->left;
    if (!IsNil(y->left)) {
      y->left->parent = x;
    }
    y->parent = GetParent(x);
    if (IsNil(x->parent)) {
      this->_root = y;
    } else if (IsLeftChild(x)) {
      x->parent->left = y;
    } else {
      x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
    return y;
  }

  pointer rightRotate(pointer x) {
    if (IsNil(x) && IsNil(x->left)) return nil;
    pointer y = x->left;
    x->left = y->right;
    if (!IsNil(y->right)) {
      y->right->parent = x;
    }
    y->parent = GetParent(x);
    if (IsNil(x->parent)) {
      this->_root = y;
    } else if (x == GetParent(x)->right) {
      x->parent->right = y;
    } else {
      x->parent->left = y;
    }
    y->right = x;
    x->parent = y;
    return y;
  }
  void dump_dot() const {
    int id = 1;
    std::cout << "digraph {\n";
    dfs(this->_root, id);
    std::cout << "}\n";
  }
};
}  // namespace ft

#endif