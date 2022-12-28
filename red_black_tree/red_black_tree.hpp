#ifndef __RED_BLACK_TREE_HPP__
#define __RED_BLACK_TREE_HPP__

// let's assume that the true value is red & the false value is black

#define red true
#define black false
#define LEFT_SIDE 0
#define RIGHT_SIDE 1

#include <fstream>   // Todo: remove this
#include <iostream>  // Todo : remove this

using namespace std;

#include "pair.hpp"
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

  Node(const T &data, pointer parent = nullptr, bool color = red) : data(data), left(nullptr), right(nullptr), parent(parent), color(color) {}

  static pointer getMinimum(const pointer tree) {
    pointer min = tree;

    while (!min->left->isNil()) {
      min = min->left;
    }
    return min;
  }

  static pointer getMaximum(const pointer tree) {
    pointer max = tree;

    while (!max->right->isNil()) {
      max = max->right;
    }
    return max;
  }

  static pointer getSuccessor(pointer x) {
    if (!x->right->isNil()) return getMinimum(x->right);

    pointer y = x->parent;
    while (!y->isNil() && y->right == x) {
      x = y;
      y = y->parent;
    }
    return y;
  }

  static pointer getPredecessor(pointer x) {
    if (!x->left->isNil()) return getMaximum(x->left);

    pointer y = x->parent;
    while (!y->isNil() && y->left == x) {
      x = y;
      y = y->parent;
    }
    return y;
  }

  template <typename Compare>
  static pointer find(const pointer tree, const value_type &val, Compare comp = Compare()) {
    pointer tmp = tree;

    while (!tmp->isNil()) {
      if (comp(val, tmp->data))
        tmp = tmp->left;
      else if (comp(tmp->data, val))
        tmp = tmp->right;
      else
        return tmp;
    }

    return tmp;
  }

  pointer getSide(short side) const { return side == LEFT_SIDE ? this->left : this->right; }
  pointer getParent(void) const { return this->parent; }
  pointer getGrandParent(void) const { return this->getParent()->getParent(); }
  pointer getSibling(void) const { return this->isLeftChild() ? this->getParent()->right : this->isRightChild() ? this->getParent()->left : nullptr; }
  pointer getUncle(void) const { return this->getGrandParent() ? (this->getParent()->isLeftChild() ? this->getGrandParent()->right : this->getGrandParent()->left) : nullptr; }

  bool isLeftChild(void) const { return this->getParent() && this == this->getParent()->left; }
  bool isRightChild(void) const { return this->getParent() && this == this->getParent()->right; }
  bool isRed(void) const { return this->color == red; }
  bool isBlack(void) const { return this->color == black; }
  bool isNil(void) const { return this != nullptr && this->left == nullptr && this->right == nullptr; }

  static void label(pointer node, int &id, ostream &stream) {
    if (!node) return;
    stream << "\tNode" << id << "[label=\"" << (!node->isNil() ? std::to_string(node->data) : "NIL") << "\""
           << ", fillcolor=\"" << (node->isRed() ? "red" : "black") << "\""
           << ", color=\"black\""
           << ", shape=" << (node->isNil() ? "record" : "circle") << ", fixedsize=true"
           << ", fontcolor=\"white\""
           << ", tooltip=\"The parent node is " << (!node->isNil() && node->parent ? std::to_string(node->parent->data) : "nil") << "\""
           << ", style=filled" << (node->isNil() ? ", width=0.3, height=0.2, fontsize=10" : ", fontsize=20") << "]\n";
  }
  static void edge(int from, int to, ostream &stream) {
    stream << "\tNode" << from << " -> "
           << "Node" << to << "[wieght=10]\n";
  }

  static int dfs(pointer tree, int &id, ostream &stream) {
    int my_id, l, r;
    my_id = id++;
    label(tree, my_id, stream);
    if (tree) {
      l = dfs(tree->left, id, stream);
      r = dfs(tree->right, id, stream);
      if (!tree->isNil()) {
        edge(my_id, l, stream);
        edge(my_id, r, stream);
      }
    }
    return my_id;
  }

  static void dump_dot(pointer tree, ostream &stream) {
    int id = 1;
    stream << "digraph {\n";
    dfs(tree, id, stream);
    stream << "}\n";
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
  pointer _nil;

 public:
  // The default constructor creates an empty container, with no elements.
  RedBlackTree() : _size(0) {
    this->_end = this->_alloc.allocate(1);
    this->_alloc.construct(this->_end, value_type());

    this->_nil = this->_alloc.allocate(1);
    this->_alloc.construct(this->_nil, value_type());
    this->_nil->color = black;

    this->_root = this->_nil;
  };

  // capacity functions
  bool      empty() const { return !this->size(); }
  size_type size() const { return this->_size; }
  size_type max_size() const { return this->_alloc.max_size(); }

  allocator_type get_allocator() const { return this->_alloc; }

  ~RedBlackTree() {
    // TODO: deallocate all nodes
    this->clean(this->_end, true);
    this->clean(this->_root);
    this->clean(this->_nil, true);
  };

  void clean(pointer node, bool deleteOne = false) {
    if (node->isNil()) return;

    pointer left = node->left;
    pointer right = node->right;
    this->_alloc.destroy(node);
    this->_alloc.deallocate(node, 1);
    if (!deleteOne) {
      clean(left);
      clean(right);
    }
  }

  void unset_end(void) {
    if (!this->_root->isNil()) {
      this->_root->parent = nullptr;
      this->_end->left = nullptr;
    }
  }

  void set_end(void) {
    if (!this->_root->isNil()) {
      this->_root->parent = this->_end;
      this->_end->left = this->_root;
    }
  }

  // iterator

  iterator       begin() { return iterator(this->size() ? this->getMinimum() : this->_end); }
  const_iterator begin() const { return const_iterator(this->size() ? this->getMinimum() : this->_end); }

  iterator       end() { return iterator(this->_end); }
  const_iterator end() const { return const_iterator(this->_end); }

  reverse_iterator       rbegin() { return reverse_iterator(this->end()); }
  const_reverse_iterator rbegin() const { return const_reverse_iterator(this->end()); }

  reverse_iterator       rend() { return reverse_iterator(this->begin()); }
  const_reverse_iterator rend() const { return const_reverse_iterator(this->begin()); }

  // red black tree functions

  ft::pair<bool, pointer> insert(const value_type &val) {
    pointer z = this->_alloc.allocate(red);
    this->_alloc.construct(z, val);
    this->_size++;

    z->left = this->_nil;
    z->right = this->_nil;
    pointer y = nullptr;
    pointer x = this->_root;

    // find the right position to put z
    while (!x->isNil()) {
      y = x;  // track the parent
      if (this->_comp(z->data, x->data))
        x = x->left;
      else
        x = x->right;
    }

    z->parent = y;
    if (y == nullptr) {
      this->_root = z;
    } else if (z->data < y->data) {
      y->left = z;
    } else {
      y->right = z;
    }

    if (z->parent == nullptr) {
      z->color = black;
    } else if (z->parent->parent != nullptr) {
      this->unset_end();
      this->insertFixUp(z);
      this->set_end();
    }
    return ft::make_pair(true, z);
  }

  void insertFixUp(pointer x) {
    pointer w;
    while (x != this->_root && x->parent->isRed()) {
      short side = x->getParent()->isRightChild() ? RIGHT_SIDE : LEFT_SIDE;
      w = x->getUncle();
      if (w->isRed()) {
        w->color = black;
        x->parent->color = black;
        x->getGrandParent()->color = red;
        x = x->getGrandParent();
      } else {
        if (x == x->parent->getSide(!side)) {
          x = x->parent;
          this->rotate(x, side);
        }
        x->parent->color = black;
        x->getGrandParent()->color = red;
        this->rotate(x->getGrandParent(), !side);
      }
    }
    this->_root->color = black;
  }

  void transplant(pointer u, pointer v) {
    if (u->parent == nullptr) {
      this->_root = v;
    } else if (u->isLeftChild()) {
      u->parent->left = v;
    } else {
      u->parent->right = v;
    }
    v->parent = u->parent;
  }

  bool deleteNode(const value_type &val) {
    pointer z = this->find(val);
    if (z->isNil()) return false;

    this->unset_end();
    pointer y = z;

    pointer x = nullptr;

    bool original_color = y->color;

    if (z->left->isNil())  // start of case 1
    {
      x = z->right;
      this->transplant(z, x);
    }                            // end of case 1
    else if (z->right->isNil())  // start of case 2
    {
      x = z->left;
      this->transplant(z, x);
    }     // end of case 2
    else  // start of case 3
    {
      y = node_type::getMinimum(z->right);
      original_color = y->color;
      x = y->right;

      if (y->getParent() == z)
        x->parent = y;
      else {
        this->transplant(y, y->right);
        y->right = z->right;
        y->right->parent = y;
      }
      this->transplant(z, y);
      y->left = z->left;
      y->left->parent = y;
      y->color = z->color;
    }  // end of case 3

    this->_alloc.destroy(z);
    this->_alloc.deallocate(z, 1);
    this->_size--;
    if (original_color == black) this->deleteFixUp(x);
    this->set_end();
    return true;
  }

  void deleteFixUp(pointer x) {
    pointer w;
    while (x != this->_root && x->color == black) {
      short side = x->isLeftChild() ? LEFT_SIDE : RIGHT_SIDE;
      w = x->getSibling();
      if (w->color == red) {  // case 1
        w->color = black;
        x->parent->color = red;
        this->rotate(x->parent, side);
        w = x->getSibling();  // end of case 1
      }

      if (w->left->color == black && w->right->color == black) {  // case 2
        w->color = red;
        x = x->getParent();  // end of case 2
      } else {
        if (w->getSide(!side)->color == black) {  // case 3
          w->getSide(side)->color = black;
          w->color = red;
          this->rotate(w, !side);
          w = x->getSibling();
        }
        w->color = x->parent->color;  // case 4
        x->parent->color = black;
        if (side == LEFT_SIDE)
          w->right->color = black;
        else
          w->left->color = black;
        this->rotate(x->parent, side);
        x = this->_root;  // end of case 4
      }
    }
    x->color = black;
  }

  // find
  pointer find(const value_type &val) { return node_type::template find<key_compare>(this->_root, val, this->_comp); }

  pointer getMinimum(void) const { return node_type::getMinimum(this->_root); }

  pointer getMaximum(void) const { return node_type::getMaximum(this->_root); }

  void rotate(pointer node, short side) {
    if (side == LEFT_SIDE)
      this->leftRotate(node);
    else
      this->rightRotate(node);
  }

  void leftRotate(pointer x) {
    pointer y = x->right;
    x->right = y->left;
    if (y->left != this->_nil) {
      y->left->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == nullptr) {
      this->_root = y;
    } else if (x->isLeftChild()) {
      x->parent->left = y;
    } else {
      x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
  }

  void rightRotate(pointer x) {
    pointer y = x->left;
    x->left = y->right;
    if (y->right != this->_nil) {
      y->right->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == nullptr) {
      this->_root = y;
    } else if (x->isRightChild()) {
      x->parent->right = y;
    } else {
      x->parent->left = y;
    }
    y->right = x;
    x->parent = y;
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