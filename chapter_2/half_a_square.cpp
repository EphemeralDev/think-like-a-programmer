#include <iostream>
using std::cin;
using std::cout;
/*

Write a program that uses only the following output statements:
 "#" and "\n" to produce the following
#####
####
###
##
#
*/

int main() {
  for (int row = 1; row <= 5; row++) {
    for (int hashNum = 1; hashNum <= 6 - row; hashNum++) {
      cout << "#";
    }
    cout << "\n";
  }
}
