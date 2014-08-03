/*
  Project Euler Problem 38
  Mikael Fors 2014

  "What is the largest 1 to 9 pandigital 9-digit number that can be formed as
   the concatenated product of an integer with (1,2, ... , n) where n > 1?"
*/

#include <iostream>

/*

  Let k be the answer. It follows that if k has 4 digits, we can get very close
  to the maximum since the first digits of the concatenation will be equal to
  k. A good start is thus to investigate 9876 - 9200 using brute force.

  Note that if k has 4 digits and is greater than 4999, we will get nine digits
  using k concat 2 * k (since 2 * k will then have five digits).

*/

bool isPandigital(int p_n) {
  int k = 1023, t = 0, r = 0;
  while(p_n > 0) {
    t = 1 << (p_n % 10);
    k ^= t;
    if(!(k & ~t) || !(k & 1))
      return false;
    p_n /= 10;
    ++r;
  }
  return (k & ((1 << (r + 1)) - 1)) == 1;
}


int main() {
  int temp = 0, answer = 0;
  
  for (int i = 9876; i > 9200; --i) {
    temp = i * 100000 + i * 2;
    if (isPandigital(temp)) {
      answer = temp;
      break;
    }
  }
  
  std::cout << "The answer is " << answer << std::endl;
  return 0;
}
