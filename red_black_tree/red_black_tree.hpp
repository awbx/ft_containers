#ifndef __RED_BLACK_TREE_HPP__
#define __RED_BLACK_TREE_HPP__

// let's assume that the true value is red & the false value is black

#define red true
#define black false
#define LEFT_SIDE 0
#define RIGHT_SIDE 1

using namespace std;

#include <iostream>

#include "pair.hpp"
#include "rbt_iterator.hpp"
#include "reverse_iterator.hpp"

namespace ft {

template <class T>
class Node {
 public:
  typedef T                 value_type;
  typedef Node<value_type> *pointer;
  typedef const pointer     const_pointer;

  // members;
  T       data;
  pointer left;
  pointer right;
  pointer parent;
  bool    color;

  Node(const T &data, pointer parent = nullptr, bool color = red) : data(data), left(nullptr), right(nullptr), parent(parent), color(color) {}

  static pointer getMinimum(const_pointer tree) {
    pointer min = tree;

    while (!min->left->isNil()) {
      min = min->left;
    }
    return min;
  }

  static pointer getMaximum(const_pointer tree) {
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
    stream << "\tNode" << id << "[label=\"" << node << "\""
           << ", fillcolor=\"" << (node->isRed() ? "red" : "black") << "\""
           << ", color=\"black\""
           << ", shape=" << (node->isNil() ? "record" : "circle") << ", fixedsize=true"
           << ", fontcolor=\"white\""
           << ", tooltip=\"The parent node is " << node->parent << "\""
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

template <typename U, typename V>
std::ostream &operator<<(std::ostream &stream, ft::pair<U, V> pr) {
  stream << pr.first;
  return stream;
}

template <typename T>
std::ostream &operator<<(std::ostream &stream, Node<T> *node) {
  if (node && !node->isNil())
    stream << node->data;
  else
    stream << "NIL";
  return stream;
}

template <typename T, typename Compare, typename Alloc>
class RedBlackTree {
 public:
  // member types
  typedef T                                                          value_type;
  typedef Node<value_type>                                           node_type;
  typedef Alloc                                                      allocator_type;
  typedef typename allocator_type::template rebind<node_type>::other node_alloc;
  typedef RedBlackTree<value_type, Compare, node_alloc>              tree;
  typedef typename node_alloc::reference                             reference;
  typedef typename node_alloc::const_reference                       const_reference;
  typedef typename node_alloc::pointer                               pointer;
  typedef typename node_alloc::const_pointer                         const_pointer;
  typedef ft::tree_iterator<node_type>                               iterator;
  typedef ft::tree_iterator<node_type>                               const_iterator;
  typedef ft::reverse_iterator<iterator>                             reverse_iterator;
  typedef ft::reverse_iterator<const_iterator>                       const_reverse_iterator;
  typedef typename node_alloc::difference_type                       difference_type;
  typedef typename node_alloc::size_type                             size_type;

 private:
  pointer    _root;
  size_type  _size;
  node_alloc _alloc;
  Compare    _comp;

  pointer _end;
  pointer _nil;

 public:
  // The default constructor creates an empty container, with no elements.
  RedBlackTree(const Compare &comp) : _size(0), _comp(comp) { this->init(); };

  void init(void) {
    this->_end = this->_alloc.allocate(1);
    this->_alloc.construct(this->_end, value_type());

    this->_nil = this->_alloc.allocate(1);
    this->_alloc.construct(this->_nil, value_type());
    this->_nil->color = black;

    this->_root = this->_nil;
  }

  RedBlackTree(const RedBlackTree &copy) : _comp(copy._comp) {
    this->init();
    *this = copy;
  }

  RedBlackTree &operator=(const RedBlackTree &rhs) {
    if (this != &rhs) {
      this->clear();

      const_iterator it = rhs.begin();
      while (it != rhs.end()) {
        this->insert(*it);
        it++;
      }
    }
    return *this;
  }

  virtual ~RedBlackTree() {
    this->clearNode(this->_end, true);
    if (this->size()) this->clearNode(this->_root);
    this->clearNode(this->_nil, true);
  };

  // capacity functions
  bool      empty() const { return !this->size(); }
  size_type size() const { return this->_size; }
  size_type max_size() const { return this->_alloc.max_size(); }

  allocator_type get_allocator() const { return this->_alloc; }

  void clear() {
    this->clearNode(this->_root);
    this->_root = this->_nil;
    this->_size = 0;
  }

  void clearNode(pointer node, bool deleteOne = false) {
    if (node->isNil()) return;

    pointer left = node->left;
    pointer right = node->right;
    this->_alloc.destroy(node);
    this->_alloc.deallocate(node, 1);
    if (!deleteOne) {
      clearNode(left, deleteOne);
      clearNode(right, deleteOne);
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

  ft::pair<bool, pointer> insertUnique(const value_type &val) {
    pointer exists = this->find(val);  // idea -> improve find function to return pair of bool & pointer
    if (!exists->isNil()) return ft::make_pair(false, exists);

    return ft::make_pair(true, this->insert(val));
  }

  pointer insert(const value_type &val) {
    // check if the val already exists !
    this->unset_end();
    pointer z = this->_alloc.allocate(red);
    this->_alloc.construct(z, val);
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
    } else if (this->_comp(z->data, y->data)) {
      y->left = z;
    } else {
      y->right = z;
    }

    if (z->parent == nullptr) {
      z->color = black;
    } else if (z->parent->parent != nullptr) {
      this->insertFixUp(z);
    }
    this->_size++;
    this->set_end();
    return z;
  }

  // This algorithm is used for maintaining the property of a red-black tree if the insertion of a newNode violates this property.

  // Do the following while the parent of newNode p is RED.
  // If p is the left child of grandParent gP of z, do the following.
  // Case-I:
  // If the color of the right child of gP of z is RED, set the color of both the children of gP as BLACK and the color of gP as RED.
  // Assign gP to newNode.
  // Case-II:
  // Else if newNode is the right child of p then, assign p to newNode.
  // Left-Rotate newNode.
  // Case-III:
  // Set color of p as BLACK and color of gP as RED.
  // Right-Rotate gP.
  // Else, do the following.
  // If the color of the left child of gP of z is RED, set the color of both the children of gP as BLACK and the color of gP as RED.
  // Assign gP to newNode.
  // Else if newNode is the left child of p then, assign p to newNode and Right-Rotate newNode.
  // Set color of p as BLACK and color of gP as RED.
  // Left-Rotate gP.
  // Set the root of the tree as BLACK.

  void insertFixUp(pointer x) {
    pointer w;
    while (x != this->_root && x->parent->isRed()) {
      short side = x->getParent()->isRightChild() ? RIGHT_SIDE : LEFT_SIDE;
      w = x->getUncle();
      if (w->isRed()) {
        // case 1 : uncle is red
        // set w to black
        // recolor x parent to black
        // recolor x grandparent to red
        // set x to x grandparent
        w->color = black;
        x->parent->color = black;
        x->getGrandParent()->color = red;
        x = x->getGrandParent();
      } else {
        if (x == x->parent->getSide(!side)) {
          // case 2 : uncle is black and x is on the other side of its parent
          // set x to x parent
          // rotate x to the same side as x parent
          x = x->parent;
          this->rotate(x, side);
        }

        // case 3 : uncle is black
        // recolor x parent to black
        // recolor x grandparent to red
        // rotate x grandparent to the other side
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

  // This algorithm is implemented when a black node is deleted because it violates the black depth property of the red-black tree.

  // This violation is corrected by assuming that node x (which is occupying y's original position) has an extra black.
  // This makes node x neither red nor black. It is either doubly black or black-and-red. This violates the red-black properties.

  // However, the color attribute of x is not changed rather the extra black is represented in x's pointing to the node.

  // The extra black can be removed if

  // It reaches the root node.
  // If x points to a red-black node. In this case, x is colored black.
  // Suitable rotations and recoloring are performed.
  // The following algorithm retains the properties of a red-black tree.

  // Do the following until the x is not the root of the tree and the color of x is BLACK
  // If x is the left child of its parent then,
  // Assign w to the sibling of x.
  // If the right child of parent of x is RED,
  // Case-I:
  // Set the color of the right child of the parent of x as BLACK.
  // Set the color of the parent of x as RED.
  // Left-Rotate the parent of x.
  // Assign the rightChild of the parent of x to w.
  // If the color of both the right and the leftChild of w is BLACK,
  // Case-II:
  // Set the color of w as RED
  // Assign the parent of x to x.
  // Else if the color of the rightChild of w is BLACK
  // Case-III:
  // Set the color of the leftChild of w as BLACK
  // Set the color of w as RED
  // Right-Rotate w.
  // Assign the rightChild of the parent of x to w.
  // If any of the above cases do not occur, then do the following.
  // Case-IV:
  // Set the color of w as the color of the parent of x.
  // Set the color of the parent of x as BLACK.
  // Set the color of the right child of w as BLACK.
  // Left-Rotate the parent of x.
  // Set x as the root of the tree.
  // Else the same as above with right changed to left and vice versa.
  // Set the color of x as BLACK.

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
  pointer find(const value_type &val) const { return node_type::template find<Compare>(this->_root, val, this->_comp); }

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

  iterator lower_bound(const value_type &k) {
    pointer node = this->_root;

    iterator iter = this->end();

    while (!node->isNil()) {
      if (!this->_comp(node->data, k)) {
        iter = iterator(node);
        node = node->left;
      } else
        node = node->right;
    }
    return iterator(iter);
  }
  const_iterator lower_bound(const value_type &k) const {
    pointer node = this->_root;

    iterator iter = this->end();

    while (!node->isNil()) {
      if (!this->_comp(node->data, k)) {
        iter = iterator(node);
        node = node->left;
      } else
        node = node->right;
    }
    return const_iterator(iter);
  }

  iterator upper_bound(const value_type &k) {
    pointer  node = this->_root;
    iterator iter = this->end();

    while (!node->isNil()) {
      if (this->_comp(k, node->data)) {
        iter = iterator(node);
        node = node->left;
      } else
        node = node->right;
    }
    return iterator(iter);
  }
  const_iterator upper_bound(const value_type &k) const {
    pointer  node = this->_root;
    iterator iter = this->end();

    while (!node->isNil()) {
      if (this->_comp(k, node->data)) {
        iter = iterator(node);
        node = node->left;
      } else
        node = node->right;
    }
    return const_iterator(iter);
  }

  void test(ostream &stream) const { node_type::dump_dot(this->_root, stream); }
};
}  // namespace ft

#endif