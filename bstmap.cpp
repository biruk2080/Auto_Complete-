// Yusuf Pisan pisan@uw.edu
// 17 Jan 2021

// BST class
// Creates a BST to store values
// Uses Node which holds the data

#include "bstmap.h"
#include <cassert>

using namespace std;

// copy constructor
BSTMap::BSTMap(const BSTMap &bst) {}

// given an array of length n
// create a tree to have all items in that array
// with the minimum height (uses same helper as rebalance)
BSTMap::BSTMap(const vector<value_type> &v) {}

// destructor
BSTMap::~BSTMap() {}

// delete all nodes in tree
void BSTMap::clear() {}

// true if no nodes in BST
bool BSTMap::empty() const { return true; }

// Number of nodes in BST
int BSTMap::size() const { return 0; }

// true if item is in BST
bool BSTMap::contains(const key_type &key) const { return true; }

// If k matches the key returns a reference to its value
// If k does not match any key, inserts a new element
// with that key and returns a reference to its mapped value.
BSTMap::mapped_type &BSTMap::operator[](const key_type &k) {
  assert(false && "operator[] has not been implemented");
  return root->data.second;
}

vector<BSTMap::value_type> BSTMap::getAll(const key_type &k) const {
  vector<value_type> v;
  return v;
}

// 0 if empty, 1 if only root, otherwise
// height of root is max height of subtrees + 1
int BSTMap::height() const { return 0; }

// height of a Node, nullptr is 0, root is 1, static, no access to 'this'
// helper function to height(), used by printVertical
int BSTMap::getHeight(const Node *n) { return 0; }

// same as contains, but returns 1 or 0
// compatibility with std::map
size_t BSTMap::count(const string &k) const { return 0; }

// inorder traversal: left-root-right
// takes a function that takes a single parameter of type T
void BSTMap::inorder(void visit(const value_type &item)) const {}

// preorder traversal: root-left-right
void BSTMap::preorder(void visit(const value_type &item)) const {}

// postorder traversal: left-right-root
void BSTMap::postorder(void visit(const value_type &item)) const {}

// balance the BST by saving all nodes to a vector inorder
// and then recreating the BST from the vector
void BSTMap::rebalance() {}

// trees are equal if they have the same structure
// AND the same item values at all the nodes
bool BSTMap::operator==(const BSTMap &other) const { return true; }

// not == to each other
bool BSTMap::operator!=(const BSTMap &other) const { return true; }
