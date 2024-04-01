#include <iostream>
#include <string>
using std::cout;
using std::string;
/*
   Problem: Tracking an Unknown Quantity of Student Records

   In this problem, you will write a class with methods to store and
   manipulate a collection of student records. A student record contains
   a student number and a grade, both integers, and a string for the student
   name. The following functions are to be implemented:

   addRecord - This method takes a student number, name, and grade and adds
   a new record with this data to the collection.

   recordWithNumber - This function takes a student number and retrieves the
   record with that student number from the collection.

   removeRecord - This function takes a student number and removes the record
   with that student number from the collection.

   The collection can be of any size. The addRecord operation is expected to
   be called frequently, so it must be implemented efficiently.
*/

class studentRecord {
  // eight member functions
  // first two are constructors
  // then a pair of member functions for each data member
  // e.g. _grade data member has two associated member functions; grade and
  // setGrade
public:
  studentRecord();
  studentRecord(int newGrade, int newID, string newName);
  int grade();
  void setGrade(int newGrade);
  int studentID();
  void setStudentID(int newID);
  string name();
  void setName(string newName);
  string letterGrade();
  bool isValidGrade(int grade);

private:
  // author uses underscore instead of keyword this
  // underscores let author name the get functions nearly the same as data
  // members, thus increasing recognition and readability
  int _grade;
  int _studentID;
  string _name;
};

bool studentRecord::isValidGrade(int grade) {
  if ((grade >= 0) && (grade <= 100))
    return true;
  else
    return false;
}

// gets the current value of grade
int studentRecord::grade() { return _grade; }
// assigns the value of newGrade to data member this.grade
// perform validation to prevent nonsensical values
void studentRecord::setGrade(int newGrade) {
  if (isValidGrade(newGrade))
    _grade = newGrade;
}

// get current value of name
string studentRecord::name() { return _name; }
// assign this.name to newName
void studentRecord::setName(string newName) { _name = newName; }

// get studentID
int studentRecord::studentID() { return _studentID; }
// set studentID
void studentRecord::setStudentID(int newID) { _studentID = newID; }

string studentRecord::letterGrade() {
  if (!isValidGrade(_grade))
    return "ERROR";
  const int NUMBER_CATEGORIES = 11;
  const string GRADE_LETTER[] = {"F",  "D", "D+", "C-", "C", "C+",
                                 "B-", "B", "B+", "A-", "A"};
  const int LOWEST_GRADE_SCORE[] = {0, 60, 67, 70, 73, 77, 80, 83, 87, 90, 93};
  int category = 0;
  while (category < NUMBER_CATEGORIES && LOWEST_GRADE_SCORE[category] <= _grade)
    category++;
  return GRADE_LETTER[category - 1];
}

// constructor with default values
// default values could cause confusion with a legitimate studentRecord
// because studentID is set with an invalid value, the record as a whole can
// easily be identified as illegitimate
studentRecord::studentRecord() {
  setGrade(0);
  setStudentID(-1);
  setName("");
}
// constructor with specified values
studentRecord::studentRecord(int newGrade, int newID, string newName) {
  setGrade(newGrade);
  setStudentID(newID);
  setName(newName);
}

// everything here on is from this exercise
class studentCollection {
private:
  struct studentNode {
    studentRecord studentData;
    studentNode *next;
  };

public:
  studentCollection();
  // note tilde distinguishes destructor from constructor
  ~studentCollection();
  void addRecord(studentRecord newStudent);
  studentRecord recordWithNumber(int idNum);
  void removeRecord(int idNum);
  // operator overload to allow = to perform a deep copy
  // operator we are overloading is specified with operator keyword followed by
  // the operator
  // rhs variable stands for right hand side, commonly chosen
  studentCollection &operator=(const studentCollection &rhs);
  studentCollection(const studentCollection &original);

private:
  typedef studentNode *studentList;
  studentList _listHead;
  void deleteList(studentList &listPtr);
  studentList copiedList(const studentList original);
};

studentCollection &studentCollection::operator=(const studentCollection &rhs) {
  // check to confirm pointers are different
  // if they were identical when performing a deep copy, when we delete the
  // nodes on the left, we also delete the nodes in the right
  if (this != &rhs) {
    // to avoid memory leak, remove all nodes from the left hand side list
    deleteList(_listHead);
    // copy the right hand list
    _listHead = copiedList(rhs._listHead);
  }
  // return a pointer to the left hand side
  return *this;
}

studentCollection::studentCollection() { _listHead = NULL; }

studentCollection::~studentCollection() { deleteList(_listHead); }

void studentCollection::addRecord(studentRecord newStudent) {
  studentNode *newNode = new studentNode;
  newNode->studentData = newStudent;
  newNode->next = _listHead;
  _listHead = newNode;
}

void studentCollection::removeRecord(int idNum) {
  studentNode *loopPtr = _listHead;
  // declare trailing pointer
  studentNode *trailing = NULL;
  while (loopPtr != NULL && loopPtr->studentData.studentID() != idNum) {
    // assign old value of loopPtr to trailing before advancing to the next node
    // this way trailing is always one node behind loopPtr
    trailing = loopPtr;
    loopPtr = loopPtr->next;
  }
  // check for NULL and return if we don't find desired idNum
  if (loopPtr == NULL)
    return;
  // handle case where deleting first node causes issue
  // deleting first node causes trouble because theres no previous node for
  // trailing to point to
  if (trailing == NULL) {
    _listHead = _listHead->next;
  } else {
    trailing->next = loopPtr->next;
  }
  // set the next field of trailing to the node currently pointed to by the next
  // field of the loopPtr node
  trailing->next = loopPtr->next;
  // now we can safely delete the node pointed to by loopPtr
  delete loopPtr;
}

studentRecord studentCollection::recordWithNumber(int idNum) {
  studentNode *loopPtr = _listHead;
  // loop checks for NULL incase there is no list or it traversed with no
  // success
  // key point: check for NULL first because C++ short circuits boolean
  // expressions
  //
  // without short circuiting, the right side of && would be
  // evaluated and we would be dereferencing a NULL pointer, crashing the
  // program
  while (loopPtr != NULL && loopPtr->studentData.studentID() != idNum) {
    loopPtr = loopPtr->next;
  }
  // if loopPtr is NULL, create dummy record and return
  if (loopPtr == NULL) {
    studentRecord dummyRecord;
    return dummyRecord;
  } else {
    return loopPtr->studentData;
  }
}

void studentCollection::deleteList(studentList &listPtr) {
  while (listPtr != NULL) {
    // copies pointer to current node to temp variable
    studentNode *temp = listPtr;
    // advances the current node pointer
    listPtr = listPtr->next;
    // deletes the node pointed to by the temp variable
    delete temp;
  }
}

// when specifying the return type in the implementation, must prefix the name
// of the class
studentCollection::studentList
studentCollection::copiedList(const studentList original) {
  // check to see if incoming list is empty
  if (original == NULL) {
    return NULL;
  }
  studentList newList = new studentNode;
  // copy first nodes data prior to loop because listHeads pointer has to be
  // modified
  newList->studentData = original->studentData;
  // traverses incoming list, always points to node we are about to copy
  studentNode *oldLoopPtr = original->next;
  // traverses new copied list, pointing to the last node created
  studentNode *newLoopPtr = newList;
  while (oldLoopPtr != NULL) {
    // create a new node
    newLoopPtr->next = new studentNode;
    // advance newLoopPtr to point to it
    newLoopPtr = newLoopPtr->next;
    // copy the data from old node to new
    newLoopPtr->studentData = oldLoopPtr->studentData;
    // advance oldLoopPtr
    oldLoopPtr = oldLoopPtr->next;
  }
  // terminate new list by assigning NULL to the next field of the last node
  newLoopPtr->next = NULL;
  // return pointer to the new list
  return newList;
}

studentCollection::studentCollection(const studentCollection &original) {
  _listHead = copiedList(original._listHead);
}

int main() {}
