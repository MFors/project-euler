/*
  Project Euler Problem 49
  Mikael Fors 2014

  "There are two 4-digit increasing arithmetic sequences of primes such that
   each prime in them is a permutation of the others. One such sequence is:

                1487, 4817, 8147  (terms increase by 3330)

   What 12-digit number do you form by concatenating the three terms in the
   other such 4-digit sequence?"
*/

#include <iostream>
#include <vector>
#include <cmath>
#include <map>
#include <boost/dynamic_bitset.hpp>
#include <algorithm>

using namespace std;

vector<int> generatePrimesUpTo(int n) {
    vector<int> primes;

    if(n < 2)
        return primes;
    primes.push_back(2);
    if(n < 3)
        return primes;
    primes.push_back(3);
    if(n < 5)
        return primes;

    int size, difference, offset, ptr, position, value, jump[2];

    size = (n / 6);
    difference = n - 6 * size;
    size = (size << 1) - (!difference ? 1 : 0) + (difference == 5 ? 1 : 0);

    boost::dynamic_bitset<> sieve(size);

    for(boost::dynamic_bitset<>::size_type i = 0; i < sieve.size(); ++i) {
        if(sieve[i])
            continue;
        offset = (i >> 1) + 1;
        value = 6 * offset + ((i & 1) ? 1 : -1);
        jump[0] = value + 2 * offset;
        jump[1] = value - 2 * offset;
        ptr = 0;
        position = i;
        while(uint(position + jump[ptr]) < sieve.size()) {
            position += jump[ptr];
            sieve[position] = 1;
            ptr ^= 1;
        }

    }

    for(boost::dynamic_bitset<>::size_type i = 0; i < sieve.size(); ++i) {
        if(!sieve[i]) {
            primes.push_back(6 * ((i >> 1) + 1) + (i & 1 ? 1 : -1));
        }
    }

    return primes;
}


void permutationPrimeSequence() {
    map<int, vector<int> > frequency;

    int k, j;
    unsigned char key[10];

    vector<int> primes = generatePrimesUpTo(9999);

    for(uint i = 0; i < primes.size(); ++i) {
        if (primes[i] < 1000)
            continue;

        k = primes[i];
        j = 0;

        // clear key
        for(int m = 0; m < 10; ++m)
            key[m] = 0;

        // count digit occurance
        while(k) {
            key[k % 10] += 1;
            k /= 10;
            ++j;
        }

        // make the key from occurances
        k = 1;
        for(int i2 = 0; i2 < 10; ++i2) {
            k *= int(pow(primes[i2], int(key[i2])));
        }

        frequency[k].push_back(primes[i]);
    }

    // Go through every bucket
    for(map<int, vector<int> >::iterator bucket = frequency.begin();
                         bucket != frequency.end(); ++bucket) {

        if(bucket->second.size() < 3)
            continue;

        // Go through each item in the bucket
        for(vector<int>::iterator start = bucket->second.begin();
                    start != bucket->second.end(); ++start) {
            // Check for numbers that follow and see if the difference
            // between current item and said item yields another item
            // if added to the end, if so we have found a series!
            for(vector<int>::iterator end = start + 1;
                    end != bucket->second.end(); ++end) {
                // We already know that 1487 is a match, so bail on it
                if(*start == 1487)
                    break;

                vector<int>::iterator match = find(
                     end + 1,
                     bucket->second.end(),
                     (*end << 1) - *start
                );

                if(match != bucket->second.end()) {
                    cout << "The answer is: "  << *start
                                               << *end
                                               << *match
                                               << endl;
                    return;
                }
            }
        }

    }

    return;
}

int main() {
    permutationPrimeSequence();
    return 0;
}
