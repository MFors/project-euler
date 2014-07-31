/*
  Project Euler Problem 28
  Mikael Fors 2014

  "Starting with the number 1 and moving to the right in a clockwise direction
   a 5 by 5 spiral is formed.

   What is the sum of the numbers on the diagonals in a 1001 by 1001 spiral
   formed in the same way?"
*/

#include <iostream>
/*

    Each direction can be simplified if we view them as series, we've got:

    A: (2 * n + 1) ^ 2           for n=1...  (n=0 yields 1)
    B: (4 * n ^ 2 - 6 * n + 3)   for n=2...  (n=1 yields 1)
    C: (4 * n ^ 2 - 10 * n + 7)  for n=2...  (n=1 yields 1)
    D: (4 * n ^ 2 + 1)           for n=1...  (n=0 yields 1)

    By setting n=m in A,D and n=m+1 in B,C we synch values in the series.
    Then all we need is to sum them together, yielding

    E: 16 * n ^ 2 + 4 * n + 4    for n=1...  (n=0 yields 1)

    Further, it is important to note that the number of times we perform
    the summing is equal to the square's side minues one divided by two,
    e.g. 5 x 5 square yields (5 - 1) >> 1 = 2 computations apart from trivial
    center (1).

*/
int main() {
  int result = 1;
  for (int n = 1; n < 501; ++n) {
    result += 16 * n * n + 4 * n + 4;
  }
  std::cout << "The answer is " << result << std::endl;
  return 0;
}
