#include <iostream>;
/*
Problem: Find the number of leaves in a binary tree
For a class that implements a binary tree, add a publicly accessible method that
returns the number of leaves (nodes without children) in the tree. The counting
of leaves should be performed using recursion.
*/

class binaryTree {
public:
  int publicCountLeaves();

private:
  struct binaryTreeNode {
    int data;
    binaryTreeNode *left;
    binaryTreeNode *right;
  };
  typedef binaryTreeNode *treePtr;
  treePtr _root;
  int privateCountLeaves(treePtr rootPtr);
};

int binaryTree::privateCountLeaves(treePtr rootPtr) {
  if (rootPtr == NULL)
    return 0;
  if (rootPtr->right == NULL && rootPtr->left == NULL)
    return 1;
  int leftCount = privateCountLeaves(rootPtr->left);
  int rightCount = privateCountLeaves(rootPtr->right);
  return leftCount + rightCount;
}

int binaryTree::publicCountLeaves() { return privateCountLeaves(_root); }

int main() {}
