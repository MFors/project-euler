/*
  Project Euler Problem 23
  Mikael Fors 2014

  "A number n is called deficient if the sum of its proper divisors is less than
   n and it is called abundant if this sum exceeds n.

   By mathematical analysis, it can be shown that all integers greater than
   28123 can be written as the sum of two abundant numbers. However, this upper
   limit cannot be reduced any further by analysis even though it is known that
   the greatest number that cannot be expressed as the sum of two abundant
   numbers is less than this limit.

  Find the sum of all the positive integers which cannot be written as the sum
   of two abundant numbers."
*/

#include <iostream>
#include <boost/dynamic_bitset.hpp>

/*
    I originally thought about factorizing numbers to generate the proper
    divisors and all that sort of stuff, but since the limit of numbers that
    we need to check is so low, I decided to utilize a sieve instead.

    The idea is that for any index k < n / 2 where n is the number of numbers
    we are interesting in finding the proper divisor sum for, all we need to
    do is look at 2 * k and add k to that index's value, then we go to 3 * k
    and so forth.

    This generates the sum for all numbers up to n, meaning all we need to do
    is to go through them and pick the abundant values. After that it is all
    about generating all combinations of the found values and marking the sum
    as reachable. After summing up all unreachable values we are done.

    Runs in 0.2s for me, slightly optimized due to lower upper bound found using
    wikipedia :)

*/

int sumOfNonAbundantSumsUpTo(int n) {
  int *divisorSumArr = new int[n + 1];
  for (int i = 0; i < n + 1; ++i)
    divisorSumArr[i] = 1;

  // sieve proper divisor sums
  for (int i = 2; i <= n / 2; ++i) {
    for (int j = 2 * i; j <= n; j += i) {
      divisorSumArr[j] += i;
    }
  }

  // pick the abundant values
  std::vector<int> abundantNumbers;
  for (int i = 12; i < n + 1; ++i) {
    if (i < divisorSumArr[i])
      abundantNumbers.push_back(i);
  }
  delete[] divisorSumArr;

  // mark all reachable sums
  boost::dynamic_bitset<> reachableSums(n + 1);
  for (auto i = abundantNumbers.begin(); i != abundantNumbers.end(); ++i) {
    for (auto j = i; *i + *j < n + 1 && j != abundantNumbers.end(); ++j) {
      reachableSums[*i + *j] = 1;
    }
  }

  // sum the unreachable values
  int result = 0;
  for (int i = 1; i < n + 1; ++i) {
    if (!reachableSums[i]) {
      result += i;
    }
  }

  return result;
}


int main() {
  std::cout << "The answer is: "
            << sumOfNonAbundantSumsUpTo(20161) << std::endl;
  return 0;
}
