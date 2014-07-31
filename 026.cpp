/*
  Project Euler Problem 21
  Mikael Fors 2014

  "Find the value of d < 1000 for which 1/d contains the longest recurring cycle
   in its decimal fraction part."
*/
   
#include <iostream>
#include <vector>
#include <boost/dynamic_bitset.hpp>
#include <unordered_map>

/*
    Currently we check all prime denominators up to 1000, but the allPrimesUpTo
    function has some overhead in terms of generating a vector for us to go
    through later, in practice all we need is the bitset.

    Further, it is possible to improve the solution even further by adding a
    cache in the global scope (in main at least) where we store previous chain
    distances, i.e. if we know that nom=x will generate a chain of abcde all we
    need to do is to search through it until we reach n s.t. n is cached in the
    function. We then return cache[n] + i + 1, where i is the index of n in
    globalCache[x].

    As the current solution runs in 1s for me, I have bailed on these things for
    now... :)

*/

template<typename T>
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

int recurringFractionCycleLength(int n) {
  // We cache previous elements and keep track of how many cycles it has been
  // since we last saw them, once we reach a previous element all we need to do
  // is to return the cycle count!
  std::unordered_map<int, int> cache;
  int nom = 1, current = 0;

  while (nom) {
    while (nom < n) {
      if (cache.find(nom) != cache.end()) {
        return cache[nom];
      } else {
        for (auto it = cache.begin(); it != cache.end(); ++it) {
          cache[it->first] += 1;
        }
        cache[nom] = 1;
        nom *= 10;
      }
    }
    current = nom / n;
    nom -= current * n;
    if (cache.find(nom) != cache.end()) {
      return cache[nom];
    } else {
      for (auto it = cache.begin(); it != cache.end(); ++it) {
        cache[it->first] += 1;
      }
      cache[nom] = 1;
      nom *= 10;
    }
  }
  return cache[nom];
}

int main() {
  int maxVal = 0, maxCount = 0, temp = 0;
  std::vector<int> validPrimes = allPrimesUpTo(1000);
  for (auto it = validPrimes.begin(); it != validPrimes.end(); ++it) {
    temp = recurringFractionCycleLength(*it);
    if (temp > maxCount) {
      maxCount = temp;
      maxVal = *it;
    }
  }
  std::cout << "The answer is: " << maxVal << std::endl;
  return 0;
}
