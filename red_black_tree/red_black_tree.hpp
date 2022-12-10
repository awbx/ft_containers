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

#define ReColor(x) ((x)->color ^= 1);

#include <iomanip>
#include <iostream>

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
    if (x->right != nil) return getMinimum(x->right);
    pointer y = x->parent;
    while (y != nil && y->right == x) {
      x = y;
      y = y->parent;
    }
    return y;
  }

  static pointer getPredecessor(pointer x) {
    if (x->left != nil) return getMaximum(x->left);

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
  typedef RedBlackTree<value_type, key_compare, allocator_type>      tree;
  typedef typename node_alloc::reference                             reference;
  typedef typename node_alloc::const_reference                       const_reference;
  typedef typename node_alloc::pointer                               pointer;
  typedef typename node_alloc::const_pointer                         const_pointer;
  typedef typename node_alloc::difference_type                       difference_type;
  typedef typename node_alloc::size_type                             size_type;

 private:
  pointer     _root;
  size_type   _size;
  node_alloc  _alloc;
  key_compare _comp;

 public:
  // The default constructor creates an empty container, with no elements.
  RedBlackTree() : _root(nil), _size(0){};

  // capacity functions
  bool      empty() const { return !this->size(); }
  size_type size() const { return this->_size; }
  size_type max_size() const { return this->_alloc.max_size(); }

  allocator_type get_allocator() const { return this->_alloc; }

  ~RedBlackTree(){
      // TODO: deallocate all nodes
  };

  // red black tree functions

  void insert(const value_type &val) {
    this->_root = insert(this->_root, val, nil);
    this->_size++;
  }

  pointer insert(pointer root, const value_type &val, pointer parent) {
    if (IsNil(root)) {
      pointer new_node = this->_alloc.allocate(1);
      this->_alloc.construct(new_node, val);
      new_node->parent = parent;
      return new_node;
    }

    if (this->_comp(val, root->data))
      root->left = insert(root->left, val, root);
    else
      root->right = insert(root->right, val, root);
    return root;
  }

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