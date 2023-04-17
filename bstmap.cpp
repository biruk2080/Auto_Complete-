// Biruk Geletu
// 04/16/2023
// BST class
// Creates a BST to store values
// Uses Node which holds the data
#include "bstmap.h"
#include <boost/algorithm/string.hpp>
#include <cassert>
#include <iostream>
using namespace std;
// default constructor
BSTMap::BSTMap() { root = nullptr; }
// copy constructor
BSTMap::BSTMap(const BSTMap &bst) { this->copyTree(bst.root); }
// given an array of length n
// create a tree to have all items in that array
// with the minimum height (uses same helper as rebalance)
BSTMap::BSTMap(const vector<value_type> &v) {
  int first = 0;
  int last = v.size() - 1;
  root = BSTree(v, first, last);
}

// destructor
BSTMap::~BSTMap() { clear(); }

// delete all nodes in tree
void BSTMap::clear() {
  if (root == nullptr) {
    return;
  }
  deleteTree(root);
  root = nullptr;
}

// true if no nodes in BST
bool BSTMap::empty() const { return (root == nullptr); }

// Number of nodes in BST
int BSTMap::size() const { return size(root); }
// true if item is in BST
bool BSTMap::contains(const key_type &key) const { return contains(root, key); }
// If k matches the key returns a reference to its value
// If k does not match any key, inserts a new element
// with that key and returns a reference to its mapped value.
BSTMap::mapped_type &BSTMap::operator[](const key_type &k) {
  Node *node = search(this->root, k);
  if (node != nullptr) {
    return node->data.second;
  }
  value_type item = value_type(k, mapped_type{});
  return insert(item);
}
// returns a vector of pair objects that match to the key (not sorted)
vector<BSTMap::value_type> BSTMap::getAll(const key_type &k) const {
  vector<value_type> v;
  getAll(v, root, k);
  return v;
}
// 0 if empty, 1 if only root, otherwise
// height of root is max height of subtrees + 1
int BSTMap::height() const { return getHeight(root); }
// height of a Node, nullptr is 0, root is 1, static, no access to 'this'
// helper function to height(), used by printVertical
int BSTMap::getHeight(const Node *n) {
  if (n == nullptr) {
    return 0;
  }
  return 1 + max(getHeight(n->left), getHeight(n->right));
}

// same as contains, but returns 1 or 0
// compatibility with std::map
size_t BSTMap::count(const string &k) const {
  if (contains(root, k)) {
    return 1;
  }
  return 0;
}

// inorder traversal: left-root-right
// takes a function that takes a single parameter of type T
void BSTMap::inorder(void visit(const value_type &item)) const {
  inOrder(root, visit);
}

// preorder traversal: root-left-right
void BSTMap::preorder(void visit(const value_type &item)) const {
  preOrder(root, visit);
}

// postorder traversal: left-right-root
void BSTMap::postorder(void visit(const value_type &item)) const {
  postOrder(root, visit);
}

// balance the BST by saving all nodes to a vector inorder
// and then recreating the BST from the vector
void BSTMap::rebalance() {
  vector<value_type> v;
  saveTree(root, v);
  deleteTree(root);
  root = BSTree(v, 0, (v.size() - 1));
}

// trees are equal if they have the same structure
// AND the same item values at all the nodes
bool BSTMap::operator==(const BSTMap &other) const {

  return isTreeSame(root, other.root);
}

// not == to each other
bool BSTMap::operator!=(const BSTMap &other) const {
  return !isTreeSame(root, other.root);
}

/// Helper Functions ///

// create new node function
BSTMap::Node *BSTMap::newNode(const value_type &item) {
  auto *node = new Node();
  node->data = item;
  node->left = nullptr;
  node->right = nullptr;
  return node;
}
// create a tree
BSTMap::Node *BSTMap::BSTree(const vector<value_type> &v, const int &first,
                             const int &last) {
  if (first > last) {
    return nullptr;
  }
  int mid = first + (last - first) / 2;
  Node *temp = newNode(v[mid]);
  temp->left = BSTree(v, first, mid - 1);
  temp->right = BSTree(v, mid + 1, last);
  return temp;
}
// counting the number of node in BST recursivily
int BSTMap::size(Node *root) const {
  if (root == nullptr) {
    return 0;
  }
  return 1 + size(root->left) + size(root->right);
}
// chack the item is on the BST or not recursivily
bool BSTMap::contains(Node *n, const key_type &key) const {
  if (n == nullptr) {
    return false;
  }
  if (key == n->data.first) {
    return true;
  }
  if (key < n->data.first) {
    return contains(n->left, key);
  }
  return contains(n->right, key);
}
// inorder traversal left to right recursivily
void BSTMap::inOrder(Node *n, void visit(const value_type &item)) const {
  if (n == nullptr) {
    return;
  }
  inOrder(n->left, visit);
  visit(n->data);
  inOrder(n->right, visit);
}
// preorder traversal root - left - right recursivily
void BSTMap::preOrder(Node *n, void visit(const value_type &item)) const {
  if (n == nullptr) {
    return;
  }
  visit(n->data);
  preOrder(n->left, visit);
  preOrder(n->right, visit);
}
// postorder traversal left - right - root recursivily
void BSTMap::postOrder(Node *n, void visit(const value_type &item)) const {
  if (n == nullptr) {
    return;
  }
  postOrder(n->left, visit);
  postOrder(n->right, visit);
  visit(n->data);
}
// helper recursive deleting of all nodes in the tree
void BSTMap::deleteTree(Node *root) {
  if (root != nullptr) {
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
  }
}
// recursive function finds objects that march to the key
// adds them to a vector of pair objects
void BSTMap::getAll(vector<value_type> &v, Node *n, const key_type &k) const {
  if (n == nullptr) {
    return;
  }
  if (!boost::algorithm::starts_with(n->data.first, k)) {
    if (n->data.first < k) {
      getAll(v, n->right, k);
    } else {
      getAll(v, n->left, k);
    }
  } else {
    v.push_back(n->data);
    getAll(v, n->right, k);
    getAll(v, n->left, k);
  }
}
// save all node from the tree to vector inorder
void BSTMap::saveTree(Node *n, vector<value_type> &v) {
  if (n == nullptr) {
    return;
  }
  saveTree(n->left, v);
  v.push_back(n->data);
  saveTree(n->right, v);
}
// recursive function for == and != operators
bool BSTMap::isTreeSame(Node *n, Node *other) const {
  if (n == nullptr && other == nullptr) {
    return true;
  }
  if (n == nullptr || other == nullptr) {
    return false;
  }
  if (n->data != other->data) {
    return false;
  }
  return isTreeSame(n->left, other->left) && isTreeSame(n->right, other->right);
}
// search function to search a given key in a given BST
BSTMap::Node *BSTMap::search(Node *root, const key_type &k) const {
  if (root == nullptr || root->data.first == k) {
    return root;
  }
  if (root->data.first > k) {
    return search(root->left, k);
  }
  return search(root->right, k);
}
// insert fanction that inserts the element if no such key exists
// return the mapped_type of the item that was inserted
BSTMap::mapped_type &BSTMap::insert(const value_type &item) {
  if (root == nullptr) {
    root = newNode(item);
    return root->data.second;
  }
  Node *curr = recursiveInsert(root, item);
  return curr->data.second;
}
// recursive insert helper function that return the Node
// of the item that was inserted
BSTMap::Node *BSTMap::recursiveInsert(Node *curr, const value_type &item) {
  if (curr->data < item) {
    if (curr->right == nullptr) {
      Node *insertNode = newNode(item);
      curr->right = insertNode;
      curr = curr->right;
    } else {
      return recursiveInsert(curr->right, item);
    }
  } else if (curr->data > item) {
    if (curr->left == nullptr) {
      Node *insertNode = newNode(item);
      curr->left = insertNode;
      curr = curr->left;
    } else {
      return recursiveInsert(curr->left, item);
    }
  }
  return curr;
}
// function that creates an identical copy of a tree
void BSTMap::copyTree(Node *from) {
  this->insert(from->data);
  if (from->left != nullptr) {
    copyTree(from->left);
  }
  if (from->right != nullptr) {
    copyTree(from->right);
  }
}
