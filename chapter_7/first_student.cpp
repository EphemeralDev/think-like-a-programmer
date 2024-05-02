#include <string>
using std::string;
/*
Problem: The First Student

At a particular school, each class has a designated "first student" who is
responsible for maintaining order in the classroom if the teacher has to leave
the room. Originally, this title was bestowed upon the student with the highest
grade, but now some teachers think the first student should be the student with
the greatest seniority, which means the lowest student ID number, as they are
assigned sequentially.

  Another faction of teachers thinks the first student
tradition is silly and intends to protest by simply choosing the student whose
name appears first in the alphabetical class roll. Our task is to modiy the
student collection class, adding a method to retrieve the first student from the
collection, while accomodating the selection criteria of the various teacher
groups.
 */

class studentRecord {
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

int studentRecord::grade() { return _grade; }
void studentRecord::setGrade(int newGrade) {
  if (isValidGrade(newGrade))
    _grade = newGrade;
}

string studentRecord::name() { return _name; }
void studentRecord::setName(string newName) { _name = newName; }

int studentRecord::studentID() { return _studentID; }
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

studentRecord::studentRecord() {
  setGrade(0);
  setStudentID(-1);
  setName("");
}

studentRecord::studentRecord(int newGrade, int newID, string newName) {
  setGrade(newGrade);
  setStudentID(newID);
  setName(newName);
}

typedef bool (*firstStudentPolicy)(studentRecord r1, studentRecord r2);

class studentCollection {
private:
  struct studentNode {
    studentRecord studentData;
    studentNode *next;
  };

public:
  studentCollection();
  ~studentCollection();
  void addRecord(studentRecord newStudent);
  studentRecord recordWithNumber(int idNum);
  void removeRecord(int idNum);
  void setFirstStudentPolicy(firstStudentPolicy f);
  studentRecord firstStudent();
  studentCollection &operator=(const studentCollection &rhs);
  studentCollection(const studentCollection &original);

private:
  firstStudentPolicy _currentPolicy;
  typedef studentNode *studentList;
  studentList _listHead;
  void deleteList(studentList &listPtr);
  studentList copiedList(const studentList original);
};

studentCollection &studentCollection::operator=(const studentCollection &rhs) {
  if (this != &rhs) {
    deleteList(_listHead);
    _listHead = copiedList(rhs._listHead);
  }
  return *this;
}

studentCollection::studentCollection() {
  _listHead = NULL;
  _currentPolicy = NULL;
}

studentCollection::~studentCollection() { deleteList(_listHead); }

void studentCollection::addRecord(studentRecord newStudent) {
  studentNode *newNode = new studentNode;
  newNode->studentData = newStudent;
  newNode->next = _listHead;
  _listHead = newNode;
}

void studentCollection::removeRecord(int idNum) {
  studentNode *loopPtr = _listHead;
  studentNode *trailing = NULL;
  while (loopPtr != NULL && loopPtr->studentData.studentID() != idNum) {
    trailing = loopPtr;
    loopPtr = loopPtr->next;
  }
  if (loopPtr == NULL)
    return;
  if (trailing == NULL) {
    _listHead = _listHead->next;
  } else {
    trailing->next = loopPtr->next;
  }
  trailing->next = loopPtr->next;
  delete loopPtr;
}

studentRecord studentCollection::recordWithNumber(int idNum) {
  studentNode *loopPtr = _listHead;
  while (loopPtr != NULL && loopPtr->studentData.studentID() != idNum) {
    loopPtr = loopPtr->next;
  }
  if (loopPtr == NULL) {
    studentRecord dummyRecord;
    return dummyRecord;
  } else {
    return loopPtr->studentData;
  }
}

void studentCollection::deleteList(studentList &listPtr) {
  while (listPtr != NULL) {
    studentNode *temp = listPtr;
    listPtr = listPtr->next;
    delete temp;
  }
}

studentCollection::studentList
studentCollection::copiedList(const studentList original) {
  if (original == NULL) {
    return NULL;
  }
  studentList newList = new studentNode;
  newList->studentData = original->studentData;
  studentNode *oldLoopPtr = original->next;
  studentNode *newLoopPtr = newList;
  while (oldLoopPtr != NULL) {
    newLoopPtr->next = new studentNode;
    newLoopPtr = newLoopPtr->next;
    newLoopPtr->studentData = oldLoopPtr->studentData;
    oldLoopPtr = oldLoopPtr->next;
  }
  newLoopPtr->next = NULL;
  return newList;
}

studentCollection::studentCollection(const studentCollection &original) {
  _listHead = copiedList(original._listHead);
}

studentRecord studentCollection::firstStudent() {
  if (_listHead == NULL || _currentPolicy == NULL) {
    studentRecord dummyRecord(-1, -1, "");
    return dummyRecord;
  }
  studentNode *loopPtr = _listHead;
  studentRecord first = loopPtr->studentData;
  loopPtr = loopPtr->next;
  while (loopPtr != NULL) {
    if (_currentPolicy(loopPtr->studentData, first)) {
      first = loopPtr->studentData;
    }
    loopPtr = loopPtr->next;
  }
  return first;
}

bool higherGrade(studentRecord r1, studentRecord r2) {
  return r1.grade() > r2.grade();
}

bool lowerStudentNumber(studentRecord r1, studentRecord r2) {
  return r1.studentID() < r2.studentID();
}

bool nameComesFirst(studentRecord r1, studentRecord r2) {
  return strcmp(r1.name().c_str(), r2.name().c_str()) < 0;
}

void studentCollection::setFirstStudentPolicy(firstStudentPolicy f) {
  _currentPolicy = f;
}

int main() {}
