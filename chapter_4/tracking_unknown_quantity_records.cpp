/*
   Problem: Tracking an unknown quantity of student records

   In this problem, you will write functions to store and manipulate a
   collection of student records. A student record contains a student
   number and a grade, both integers. The following functions are to be
   implemented.

   addRecord - This function takes a pointer to a collection of student
   records (a student number and a grade), and it adds a new record with
   this data to the collection.

   averageRecord - This function takes a pointer to a collection of student
   records and returns the simple average of student grades in the collection
   as a double.

   The collection can be of any size. The addRecord operation is expected to
   be called frequently, so it must be implemented efficiently.
*/

struct listNode {
  int studentNum;
  int grade;
  // Pointer to the very struct we're defining
  listNode *next;
};
// pointer to node type
typedef listNode *studentCollection;

// declares studentCollection sc which will eventually become the name for our
// linked list
studentCollection sc;

void addRecord(studentCollection &sc, int stuNum, int gr) {
  // create new node
  listNode *newNode = new listNode;
  // assign studentNum from parameter
  newNode->studentNum = stuNum;
  // assign grade from parameter
  newNode->grade = gr;
  // link new node to the list
  // point the next field of newNode to the former first node
  // following two steps must happen in that order
  // need to use sc before we change it
  // because sc is changed, it must be reference parameter
  newNode->next = sc;
  // point the linked list at thew new node newNode
  sc = newNode;
}

double averageRecord(studentCollection sc) {
  // handle edge case of empty list
  if (sc == NULL)
    return 0;
  // count number of nodes encountered in list
  int count = 0;
  // running total of grade values in list
  double sum = 0;
  // variable to track/traverse the list
  listNode *loopPtr = sc;
  while (loopPtr != NULL) {
    // add value of grade field in current node to sum
    sum += loopPtr->grade;
    count++;
    // assign the next field of the current node to loop tracking pointer
    loopPtr = loopPtr->next;
  }
  double average = sum / count;
  return average;
}

int main() {
  // declare node1 and point to newly allocated listNode in heap
  listNode *node1 = new listNode;
  // assign values to studentNum and grade fields in each node
  node1->studentNum = 1001;
  node1->grade = 78;
  listNode *node2 = new listNode;
  node2->studentNum = 1012;
  node1->grade = 93;
  listNode *node3 = new listNode;
  node3->studentNum = 1076;
  node3->grade = 85;
  // Now that all nodes exist and are populated, we can string them together
  // point our studentCollection variable sc to the first node
  sc = node1;
  // point the next field of node1 to node2
  node1->next = node2;
  // point next field of node2 to node3
  node2->next = node3;
  // assign NULL to the next field in node3
  // terminates the structure
  node3->next = NULL;
  // to cleanup and prevent cross-linking we assign NULL to each of the
  // individual node pointers
  node1 = node2 = node3 = NULL;

  addRecord(sc, 1274, 91);
  int avg = averageRecord(sc);
}
