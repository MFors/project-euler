/*
  Project Euler Problem 32
  Mikael Fors 2014

  "Find the sum of all products whose multiplicand/multiplier/product identity
   can be written as a 1 through 9 pandigital"
*/

#include <iostream>
#include <unordered_map>
#include <vector>

/*

    Brute force since we can restrict the loops quite a bit.
    Dupes avoided by using hashmap.

    Runs in 3ms for me, pretty okay.

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


std::vector<long> pandigitalProducts() {
  std::unordered_map<long, bool> productMap;
  std::vector<long> result;

  int product = 0, temp = 0, digitCount = 0, over = 0;
  long concatNumber = 0;
  bool firstRun = true, thirdRun = false;

  // i x j, where j > i, it follows that i is max 79 as
  // 79 * 123 = 9717  (concatenated length 9)
  // 84 * 123 = 10332 (concatenated length 10)
  for (int i = 1; i < 79; ++i) {
    if (!(i % 10)) // cannot have 0
      continue;
    for (int j = i + 1; ;++j) {
      temp = j;
      product = i * j;
      concatNumber = i;
      digitCount = 0;

      // Concatenate the numbers and count length
      firstRun = true, thirdRun = false;
      while (temp) {
        if (!thirdRun) {
          over = temp % 10;
          if (!over)
            break; // A zero means it is not pandigital
          concatNumber *= 10;
          concatNumber += over;
        }
        temp /= 10;
        ++digitCount;
        if (firstRun && !temp) {
          temp = product;
          firstRun = false;
        } else if (!temp && !thirdRun && !firstRun) {
          temp = i;
          thirdRun = true;
        }
      }

      if (digitCount > 9)
        break;
      if (digitCount < 9 || !isPandigital(concatNumber))
        continue;
      productMap[product] = true;
    }
  }

  for (auto product = productMap.begin();
      product != productMap.end(); ++product) {
    result.push_back(product->first);
  }

  return result;
}


int main() {
  std::vector<long> products = pandigitalProducts();
  int result = 0;
  for (auto product = products.begin(); product != products.end(); ++product)
    result += *product;
  std::cout << "The answer is " << result;
  return 0;
}
