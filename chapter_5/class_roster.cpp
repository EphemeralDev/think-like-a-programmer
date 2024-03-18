#include <iostream>
#include <string>
using std::cout;
using std::string;
/*
Problem: Class Roster

Design a class or set of classes for use in a program that maintains a
roster. For each student, store the student's name, ID, and final grade
score in the range 0 - 100. The program will allow student records to be
added or removed; display the record of a particular student, identified
by ID, with the grade displayed as a number and as a letter; and display
the average score for the class. The appropriate letter grade for a
particular score is shown in table 5-1.

Letter Grades

Score Range     Letter Grade
93-100          A
90-92           A-
87-89           B+
83-86           B
80-82           B-
77-79           C+
73-76           C
70-72           C-
67-69           D+
60-66           D
0-59            F
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

int main() {
  studentRecord Test(90, 10, "Tux");
  cout << Test.grade() << " " << Test.studentID() << " " << Test.name() << "\n";
}
