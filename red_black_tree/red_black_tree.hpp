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
struct Node {
  T     data;
  Node *left;
  Node *right;
  Node *parent;
  bool  color;

  Node(const T &data, Node *parent = nil, bool color = true) : data(data), left(nil), right(nil), parent(parent), color(color) {}
};

template <typename T, typename Compare, typename Alloc>
class RedBlackTree {
 public:
  // member types
  typedef T                                                                                           value_type;
  typedef Node<value_type>                                                                            node_type;
  typedef Compare                                                                                     key_compare;
  typedef Alloc                                                                                       allocator_type;
  typedef typename allocator_type::template rebind<Node<std::pair<const int, const char *> > >::other node_alloc;
  typedef typename node_alloc::reference                                                              reference;
  typedef typename node_alloc::const_reference                                                        const_reference;
  typedef typename node_alloc::pointer                                                                pointer;
  typedef typename node_alloc::const_pointer                                                          const_pointer;
  typedef typename node_alloc::difference_type                                                        difference_type;
  typedef typename node_alloc::size_type                                                              size_type;

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

  pointer getMinimum(void) const { return this->getMinimum(this->_root); }
  pointer getMinimum(const pointer tree) const {
    pointer min = tree;

    while (min && min->left) {
      min = min->left;
    }
    return min;
  }

  pointer getMaximum(void) const { return this->getMaximum(this->_root); }
  pointer getMaximum(const pointer tree) const {
    pointer max = tree;

    while (max && max->right) {
      max = max->right;
    }
    return max;
  }

  pointer getSuccessor(pointer x) const {
    if (x->right != nil) return this->getMinimum(x->right);
    pointer y = x->parent;
    while (y != nil && y->right == x) {
      x = y;
      y = y->parent;
    }
    return y;
  }

    while (max && max->right) {
      max = max->right;
    }
    return max;
  }
  static void label(pointer node, int &id) {
    std::cout << "\tNode" << id << "[label=\"" << (node ? std::to_string(node->data.first) : "NIL") << "\""
              << ", fillcolor=\"" << (IsRed(node) ? "red" : "black") << "\""
              << ", color=\"black\""
              << ", shape=" << (IsNil(node) ? "record" : "circle") << ", fixedsize=true"
              << ", fontcolor=\"white\""
              << ", tooltip=\"The parent node is " << (node && node->parent ? std::to_string(node->parent->data.first) : "nil") << "\""
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
  void dump_dot() const {
    int id = 1;
    std::cout << "digraph {\n";
    dfs(this->_root, id);
    std::cout << "}\n";
  }
};
}  // namespace ft

#endif