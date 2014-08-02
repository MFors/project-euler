/*
  Project Euler Problem 33
  Mikael Fors 2014

  "The fraction 49/98 is a curious fraction, as an inexperienced mathematician
   in attempting to simplify it may incorrectly believe that 49/98 = 4/8, which
   is correct, is obtained by cancelling the 9s.

   We shall consider fractions like, 30/50 = 3/5, to be trivial examples.

   There are exactly four non-trivial examples of this type of fraction, less
   than one in value, and containing two digits in the numerator and denominator.

   If the product of these four fractions is given in its lowest common terms,
   find the value of the denominator."
*/

#include <iostream>
#include <vector>
#include <cmath>
#include <boost/dynamic_bitset.hpp>

/*
    Used bruteforce since the number of potential fractions are so few.
    After finding all fractions it is just a matter of finding the gcd and
    dividing the denominator with it. Easy!
*/

template <typename T>
std::vector<T> allPrimesUpTo(T p_n) {
  // Eliminate trivial cases
  if(p_n < 2)
    return std::vector<T>{};
  if(p_n < 3)
    return std::vector<T>{2};
  if(p_n < 5)
    return std::vector<T>{2, 3};

  T size = (p_n / 6),
    difference = (p_n - 6 * size),
    offset,
    ptr,
    position,
    value,
    jump[2];

  T counter = 2;

  size = (size << 1) - (!difference ? 1 : 0) + (difference == 5 ? 1 : 0);

  // Bit Sieve where 0 (default) <=> prime and 1 <=> composite
  boost::dynamic_bitset<> sieve(size);

  T sSize = (T)sieve.size(); // conversion cached for while-loop

  for(auto i = 0; i < sieve.size(); ++i) {
    if(sieve[i])
      continue;
    ++counter;
    offset = (i >> 1) + 1;
    value = 6 * offset + ((i & 1) ? 1 : -1);
    offset <<= 1;
    jump[0] = value + offset;
    jump[1] = value - offset;
    ptr = 0;
    position = i;

    while(position + jump[ptr] < sSize) {
      position += jump[ptr];
      sieve[position] = 1;
      ptr ^= 1;
    }
  }

  T* primes = new T[counter];
  primes[0] = 2;
  primes[1] = 3;

  T pos = 2;

  for(boost::dynamic_bitset<>::size_type i = 0; i < sieve.size(); ++i) {
    if(!sieve[i]) {
      primes[pos] = 6 * ((i >> 1) + 1) + (i & 1 ? 1 : - 1);
      ++pos;
    }
  }

  std::vector<T> result(primes, primes + counter);
  delete[] primes;
  return result;
}


std::vector<int> sharedFactors(int p_first, int p_second) {
  int maxPrimeRange = std::sqrt(std::max(p_first, p_second));
  std::vector<int> primes = allPrimesUpTo(maxPrimeRange), result;

  for (auto prime = primes.begin(); prime != primes.end(); ++prime) {
    while (!(p_first % *prime) && !(p_second % *prime)) {
      p_first /= *prime;
      p_second /= *prime;
      result.push_back(*prime);
    }
  }

  if (p_first != 1 && p_first == p_second)
    result.push_back(p_first);

  return result;
}


std::vector<std::pair<int, int>> generateValidFractions() {
  std::vector<std::pair<int, int>> result;
  bool shouldPush = false;
  double originalValue = 0;
  int iFirst = 0, iSecond = 0, jFirst = 0, jSecond = 0;

  for (int i = 10; i < 100; ++i) {
    for (int j = i + 1; j < 100; ++j) {
      // do they share a digit?
      shouldPush = false;
      iFirst = i / 10, iSecond = i % 10;
      jFirst = j / 10, jSecond = j % 10;

      if (!iSecond || !jSecond)
        continue; // Trivial case (multiples of 10)


      // Using double will not be a problem here since the noms/denoms have such
      // limited precision (2-digit)
      originalValue = i / double(j);

      if (iFirst == jFirst) {
        shouldPush = originalValue == iSecond / (double)jSecond;
      } else if (iFirst == jSecond) {
        shouldPush = originalValue == iSecond / (double)jFirst;
      } else if (iSecond == jFirst) {
        shouldPush = originalValue == iFirst / (double)jSecond;
      } else if (iSecond == jSecond) {
        shouldPush = originalValue == iFirst / (double)jFirst;
      }

      if (shouldPush)
        result.push_back((std::pair<int, int>){i, j});
    }
  }
  return result;
}


int main() {
  std::vector<std::pair<int, int>> validFractions = generateValidFractions();
  std::pair<int, int> resultingFraction{1, 1};

  for (auto pair = validFractions.begin();
      pair != validFractions.end(); ++pair) {
    resultingFraction.first *= (*pair).first;
    resultingFraction.second *= (*pair).second;
  }

  std::vector<int> commonFactors = sharedFactors(resultingFraction.first,
      resultingFraction.second);

  for (auto factor = commonFactors.begin();
      factor != commonFactors.end(); ++factor)
    resultingFraction.second /= *factor;

  std::cout << "The answer is " << resultingFraction.second << std::endl;
  return 0;
}
