#include <iostream>
using std::cout;
/*
Problem: Variable-Length String Manipulation

Write heap-based implementations for three required string functions:

append - This function takes a string and a character and appends the
character to the end of the string.

concatenate - This function takes two strings and appends the characters
of the second string onto the first.

characterAt - This function takes a string and a number and returns the
character at that position in the string (with the first character in the
string numbered zero).

Write the code with the assumption that characterAt will be called
frequently while the other two functions will be called reletively seldom.
The relative efficiency of the operations should reflect the calling
frequency.
*/

// We're dynamically creating arrays
// so we make our string type a pointer to a char
typedef char *arrayString;

char characterAt(arrayString s, int position) { return s[position]; }

// length split to its own function for reuse in append and concatenate
int length(arrayString s) {
  int count = 0;
  while (s[count] != 0) {
    count++;
  }
  return count;
}

void append(arrayString &s, char c) {
  // counts length by locating null char
  int oldLength = length(s);
  // allocate a new array with size of oldArray + 2
  arrayString newS = new char[oldLength + 2];
  // copy legitimate chars from old array to new
  for (int i = 0; i < oldLength; i++) {
    newS[i] = s[i];
  }

  // assign the appended char to appropriate location
  newS[oldLength] = c;
  // assign terminator to appropriate location
  newS[oldLength + 1] = 0;
  // deallocate the array s pointed to
  // prevent memory leak
  delete[] s;
  // point s to new array
  s = newS;
}

void appendTester() {
  arrayString a = new char[5];
  a[0] = 't';
  a[1] = 'e';
  a[2] = 's';
  a[3] = 't';
  a[4] = 0;
  append(a, '!');
  cout << a << "\n";

  arrayString b = new char[1];
  b[0] = 0;
  append(b, '!');
  cout << b << "\n";
}

void concatenate(arrayString &s1, arrayString s2) {
  // determine lengths of strings we're concatenating
  int s1_OldLength = length(s1);
  int s2_Length = length(s2);
  // sum values of both strings to determine length of concatenated string
  int s1_NewLength = s1_OldLength + s2_Length;

  // create array for new string, allocating 1 more than the sum to have space
  // for the terminator
  arrayString newS = new char[s1_NewLength + 1];
  // copy chars from old strings to new
  for (int i = 0; i < s1_OldLength; i++) {
    newS[i] = s1[i];
  }
  for (int i = 0; i < s2_Length; i++) {
    // copy from the beginning of s2 into the middle of newS
    newS[s1_OldLength + i] = s2[i];
  }
  // place terminator at end of new string
  newS[s1_NewLength] = 0;
  // deallocate s1 to prevent memory leak
  delete[] s1;
  // repoint s1 to new string
  s1 = newS;
}

void concatenateTester() {
  arrayString a = new char[5];
  a[0] = 't';
  a[1] = 'e';
  a[2] = 's';
  a[3] = 't';
  a[4] = 0;
  arrayString b = new char[4];
  b[0] = 'b';
  b[1] = 'e';
  b[2] = 'd';
  b[3] = 0;
  concatenate(a, b);

  arrayString c = new char[1];
  c[0] = 0;
  concatenate(c, a);
  cout << a << "\n" << c << "\n";
  cout << (void *)a << "\n" << (void *)c << "\n";
}

int main() {
  appendTester();
  concatenateTester();
}
