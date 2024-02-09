#include <iostream>
using std::cin;
using std::cout;
/*
The Luhn formula: using the original number, double the value of
every other digit. Then add the values of the individual digits together (if a
doubled value now has two digits, add digits individually). The number is valid
if the sum is divisible by 10.

Write a program that takes an identification number of arbitrary length and
determines whether the number is valid under the Luhn formula. The program must
process each character before reading the next one. Our program only validates
the number, it does not create the check digit.
*/

int doubleDigitValue(int digit) {
  int doubledDigit = digit * 2;
  int sum;
  if (doubledDigit >= 10)
    sum = 1 + doubledDigit % 10;
  else
    sum = doubledDigit;
  return sum;
}

int main() {
  char digit;
  int oddLengthChecksum = 0;
  int evenLengthChecksum = 0;
  int checksum = 0;
  int position = 1;

  cout << "Enter a number: ";
  // Need an initial value for digit before we enter the loop
  digit = cin.get();

  // Character code 10 marks end of input. i.e. when user presses enter
  // Length of input is unknown, must calculate both odd/even checksums
  while (digit != 10) {
    if (position % 2 == 0) {
      oddLengthChecksum += doubleDigitValue(digit - '0');
      evenLengthChecksum += digit - '0';
    } else {
      oddLengthChecksum += digit - '0';
      evenLengthChecksum += doubleDigitValue(digit - '0');
    }
    // Gets each subsequent value in the loop
    digit = cin.get();
    position++;
  }

  // Subtract 1 from position to exclude the terminating end of line character
  if ((position - 1) % 2 == 0)
    checksum = evenLengthChecksum;
  else
    checksum = oddLengthChecksum;

  cout << "Checksum is " << checksum << ". \n";
  if (checksum % 10 == 0) {
    cout << "Checksum is divisible by 10. Valid \n";
  } else {
    cout << "Checksum is not divisilbe by 10. Invalid \n";
  }
}
