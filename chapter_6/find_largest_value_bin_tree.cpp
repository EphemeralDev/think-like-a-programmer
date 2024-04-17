#include <iostream>
/*
Problem: Find the largest value in a binary tree
Write a function that, when given a binary tree where each node holds an
integer, returns the largest integer in the tree.
*/

struct treeNode {
  int data;
  treeNode *left;
  treeNode *right;
};

typedef treeNode *treePtr;

int maxValue(treePtr root) {
  // empty case covered for safety
  if (root == NULL)
    return 0;
  // minimal case of tree is a single node
  if (root->right == NULL && root->left == NULL)
    return root->data;
  // recursion to find maxValue on left subtree
  int leftMax = maxValue(root->left);
  // recursion to find maxValue on right subtree
  int rightMax = maxValue(root->right);
  // find largest value using king of the hill algorithm
  int maxNum = root->data;
  if (leftMax > maxNum)
    maxNum = leftMax;
  if (rightMax > maxNum)
    maxNum = rightMax;
  return maxNum;
}

int main() {}
