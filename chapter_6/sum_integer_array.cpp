/*
Problem: Computing the sum of an array of integers

Write a recursive function that is given an array of integers and the size of
the array as parameters. The function returns the sum of the integers in the
array.
 */

int arraySumRecursive(int integers[], int size) {
  // check for and handle most trivial case
  if (size == 0)
    return 0;
  // store last number in array
  int lastNumber = integers[size - 1];
  // enforce dispatcher rule 2: pass smaller version to recursive function
  int allButLastSum = arraySumRecursive(integers, size - 1);
  return lastNumber + allButLastSum;
}

int iterativeArraySum(int integers[], int size) {
  int sum = 0;
  for (int i = 0; i < size; i++) {
    sum += integers[i];
  }
  return sum;
}

int arraySumDelegate(int integers[], int size) {
  if (size == 0)
    return 0;
  int lastNumber = integers[size - 1];
  int allButLastSum = iterativeArraySum(integers, size - 1);
  return lastNumber + allButLastSum;
}

int main() {}
