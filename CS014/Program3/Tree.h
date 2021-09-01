#ifndef __TREE_H
#define __TREE_H

#include "Node.h"

class Tree {
private:
  Node *root;

public:
  Tree();
  ~Tree();
  void insert(const string &);
  void preOrder( ) const;
  void inOrder( ) const;
  void postOrder( ) const;
  void remove(const string &);
  bool search (const string &) const;

private:
  Node* split(Node* node);
  void insert(Node* node, const string &key);
  Node* recursiveSearch(Node* node, string key) const;
  // Add additional functions/variables here
    
};

#endif
