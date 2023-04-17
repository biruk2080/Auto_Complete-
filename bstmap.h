// Biruk Geletu 
// 04/16/2023
// BST class
// Creates a BST to store values
// Uses Node which holds the data
// Uses templates to store any type of data
// binarysearchtreee.cpp file is included at the bottom of the .h file
// binarysearchtreee.cpp is part of the template, cannot be compiled separately

#ifndef BSTMAP_H
#define BSTMAP_H

#include <cstdint>
#include <iostream>
#include <queue>
#include <string>
#include <vector>

using namespace std;

class BSTMap {

  // display BST tree in a human-readable format
  // comment out printSideways or printVertical
  friend ostream &operator<<(ostream &out, const BSTMap &bst);

public:
  using key_type = string;
  using mapped_type = uint64_t;
  using value_type = pair<key_type, mapped_type>;

  // constructor, empty tree
  BSTMap();

  // copy constructor
  BSTMap(const BSTMap &bst);

  // given an array of length n
  // create a tree to have all items in that array
  // with the minimum height (uses same helper as rebalance)
  explicit BSTMap(const vector<value_type> &v);

  // destructor
  virtual ~BSTMap();

  // move not allowed
  BSTMap(BSTMap &&other);

  // assignment not allowed
  BSTMap &operator=(const BSTMap &other) = delete;

  // move assignment not allowed
  BSTMap &operator=(BSTMap &&other) = delete;

  // true if no nodes in BST
  bool empty() const;

  // Number of nodes in BST
  int size() const;

  // 0 if empty, 1 if only root, otherwise
  // height of root is max height of subtrees + 1
  int height() const;

  // delete all nodes in tree
  void clear();

  // true if item is in BST
  bool contains(const key_type &key) const;

  // same as contains, but returns 1 or 0
  // compatibility with std::map
  size_t count(const key_type &k) const;

  // If k matches the key returns a reference to its value
  // If k does not match any key, inserts a new element
  // with that key and returns a reference to its mapped value.
  mapped_type &operator[](const key_type &k);

  // inorder traversal: left-root-right
  // takes a function that takes a single parameter of type T
  void inorder(void visit(const value_type &item)) const;

  // preorder traversal: root-left-right
  void preorder(void visit(const value_type &item)) const;

  // postorder traversal: left-right-root
  void postorder(void visit(const value_type &item)) const;

  // balance the BST by saving all nodes to a vector inorder
  // and then recreating the BST from the vector
  void rebalance();

  // returns true if item successfully erased - BONUS
  bool erase(const key_type &k);

  // given a prefix string, return all values that match
  // the prefix. Traverses both branches of the tree once
  // a value matching the prefix is found.
  vector<value_type> getAll(const key_type &k) const;

  // trees are equal if they have the same structure
  // AND the same item values at all the nodes
  bool operator==(const BSTMap &other) const;

  // not == to each other
  bool operator!=(const BSTMap &other) const;

private:
  // Node for BST
  struct Node {
    // key-value pair
    value_type data;
    // children
    struct Node *left;
    struct Node *right;
  };

  // refer to data type "struct Node" as Node
  using Node = struct Node;

  // print Node
  friend ostream &operator<<(ostream &out, const Node &n);

  // root of the tree
  Node *root{nullptr};

  // print tree sideways with root on left
  static ostream &printSideways(ostream &out, const Node *curr, int level = 0);

  // helper for printVertical
  static ostream &centeredPrint(ostream &out, int space, const string &str,
                                char fillChar = ' ');

  // print tree with the root at top
  static ostream &printTreeLevel(ostream &out, queue<const Node *> &q,
                                 int width, int depth, int maxDepth);

  // helper function for displaying tree sideways, works recursively
  static ostream &printVertical(ostream &out, Node *curr);

  // height of a Node, nullptr is 0, root is 1, static, no access to 'this'
  // helper function to height(), used by printVertical
  static int getHeight(const Node *n);
  
  /// Helper Functions ///
  
  // creat a tree 
  Node* BSTree(const vector<value_type> &v, const int &first, const int &last);
  // create a new node 
  static Node* newNode(const value_type &item);
  // counting number of nodes in BST
  int size(Node *root) const;
  // chack the item is on the BST or not recursivily 
  bool contains(Node *n, const key_type &key) const;
  // inorder traversal left - root- right recursivily 
  void inOrder(Node *n, void visit(const value_type &item)) const;
  // preorder traversal root - left - right recursivily 
  void preOrder(Node *n, void visit(const value_type &item)) const;
  // postorder traversal left - right - root recursivily 
  void postOrder(Node *n, void visit(const value_type &item)) const;
  // helper recursive deleting of all nodes in the tree
void deleteTree(Node *root); 
// recursive function finds objects that march to the key
// adds them to a vector of pair objects
void getAll(vector<value_type> &v, Node *n, const key_type &k) const; 
// copy all node from the tree to vector inorder
void saveTree(Node* n, vector<value_type> &v);
// recursive function for == and != operators
bool isTreeSame(Node *n, Node *other) const;
// function to search a given key in a given BST
  Node* search(Node *root, const key_type &k) const;
  // insert fanction that inserts the element if no such item exists
  // return the mapped_type of the item that was inserted
  mapped_type& insert(const value_type &item);

  // recursive insert helper function that return the Node
  // of the item that was inserted
  Node* recursiveInsert(Node *curr, const value_type &item);
  // function that creates an identical copy of a tree
  void copyTree(Node *from); 
  // ostraem helper function that print the stree inorder recursivily 
  //void ostreamHelper(BSTMap::Node *root, ostream &out) const;
};
#endif // BSTMAP_H
