#include "Tree.h"
#include <string>


Tree::Tree() {
    root = nullptr;
 }

Tree::~Tree() {

}

void Tree::insert(const string &key) {
    if (search(key)) {
        return;
    }
    if (root == nullptr) {
        root = new Node();
        root->small = key;
        return;
    }

    if (root->large != "") {
        insert(root, key);
    } else
    { 
        if (root->small > key) {
            root->large = root->small;
            root->small = key;
        } else
        {
            root->large = key;
        }
        
    }
}

void Tree::insert(Node* node, const string &key) {
    // BTreeInsert(node, key) {
//    if (key is in node) {
//       return null // duplicates not allowed
//    }
//    if (node is full) {
//       node = BTreeSplit(node)
//    }
//    if (node is not leaf) {
//       if (key < node⇢A)
//          return BTreeInsert(node⇢left, key)
//       else if (node⇢B is null || key < node⇢B)
//          return BTreeInsert(node⇢middle1, key)
//       else if (node⇢C is null || key < node⇢C)
//          return BTreeInsert(node⇢middle2, key)
//       else
//          return BTreeInsert(node⇢right, key)
//    }
//    else {
//       BTreeInsertIntoLeaf(node, key)
//       return node
//    }
// }
}

Node* Tree::split(Node* node) {
//      if (node is not full)
//       return null
//    nodeParent = node⇢parent
//    splitLeft = new BTreeNode(node⇢A, node⇢left, node⇢middle1)
//    splitRight = new BTreeNode(node⇢C, node⇢middle2, node⇢right)
//    if (nodeParent is not null)
//       BTreeInsertKeyWithChildren(nodeParent, node⇢B, splitLeft, splitRight)
//    else {
//       nodeParent = new BTreeNode(node⇢B, splitLeft, splitRight)
//       tree⇢root = nodeParent
//    }
//    return nodeParent
}

void Tree::preOrder() const {

}
void Tree::inOrder( ) const {

}
void Tree::postOrder( ) const {

}
void Tree::remove(const string &) {

}

bool Tree::search (const string &key) const {
    Node* temp = recursiveSearch(root, key);
    if (temp != nullptr) {
        return true;
    } else
        return false;
}

Node* Tree::recursiveSearch(Node* node, string key) const {
    if (node != nullptr) {
        if (key == node->small || key == node->large) {
            return node;
        }
        if (key < node->small) {
            return  recursiveSearch(node->left, key);
        }
        else if (key > node->small && key < node->large) {
            return recursiveSearch(node->middle, key);
        }
        else if (key > node->large) {
            return recursiveSearch(node->right, key);
        }
    }
    return nullptr;
}