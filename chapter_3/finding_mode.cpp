#include <iostream>
using std::cin;
using std::cout;

/*
Problem: Finding the Mode

In statistics, the mode of a set of values is the value that appears most
often. Write code that processes an array of survey data, where the survey
takers have responded to a question with a number in the range 1-10, to
determine the mode of the data set. For our purpose, if multiple modes
exist, any may be chosen.
*/

int main() {
  const int ARRAY_SIZE = 12;
  int surveyData[ARRAY_SIZE] = {4, 7, 3, 8, 9, 7, 3, 9, 9, 3, 3, 10};

  // Print the array to stdout
  for (int i = 0; i < ARRAY_SIZE; i++) {
    cout << surveyData[i] << ' ';
  }

  // Initialize values to 0
  const int MAX_RESPONSE = 10;
  int histogram[MAX_RESPONSE];
  for (int i = 0; i < MAX_RESPONSE; i++) {
    histogram[i] = 0;
  }

  // Count occurences of each value
  for (int i = 0; i < ARRAY_SIZE; i++) {
    histogram[surveyData[i] - 1]++;
  }

  // Determine mode
  int mostFrequent = 0;
  for (int i = 1; i < MAX_RESPONSE; i++) {
    if (histogram[i] > histogram[mostFrequent])
      mostFrequent = i;
  }
  // Increment to get the correct array position
  mostFrequent++;
  cout << '\n' << "The mode is " << mostFrequent;
}
