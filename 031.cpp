/*
  Project Euler Problem 31
  Mikael Fors 2014

  "How many different ways can £2 be made using any number of the following
   coins: 1p, 2p, 5p, 10p, 20p, 50p, £1, £2?"
*/

#include <iostream>

/*
    Given p and a sum s, it follows that if we move from smaller sums to 200,
    any leftover from s - p is already computed since s - p < p. If we make
    sure to utilize increasing p throughout, the buildup will also always ensure
    that only small coins are used (if p=5, we can only see ways with p<=5 for
    smaller s - p and so forth).

    Note that we malloc 201 elements simply to remove the need for us to convert
    values to indices (values[k] - 1 for actual). Further, letting ways[0] be
    1 eliminates the need for us to verify that j - values[i] is true.

*/

int main() {
  int ways[201] = {1}, values[8] = {1, 2, 5, 10, 20, 50, 100, 200};

  for (int i = 0; i < 8; ++i) {
    for (int j = values[i]; j <= values[7]; ++j) {
      ways[j] += ways[j - values[i]];
    }
  }

  std::cout << "The answer is: " << ways[200] << std::endl;
  return 0;
}
