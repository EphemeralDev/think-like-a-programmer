#include <iostream>
/*
Problem: Counting negative numbers in a singly linked list

Write a recursive function that is given a singly linked list where the data
type is integer. The function returns the count of negative numbers in the list.
*/

struct listNode {
  int data;
  listNode *next;
};

typedef listNode *listPtr;

int countNegative(listPtr head) {
  if (head == NULL)
    return 0;
  int listCount = countNegative(head->next);
  if (head->data < 0)
    listCount++;
  return listCount;
}

int main() {}
