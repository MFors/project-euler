/*
  Project Euler Problem 50
  Mikael Fors 2014
  
  "Which prime, below one-million, can be written as the sum 
   of the most consecutive primes?
*/

#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <boost/dynamic_bitset.hpp>

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

struct Candidate {
    int value;
    int first;
    int last;
};

int sumOfLongestPrimeSumUnder(int n) {
    vector<int> primes = generatePrimesUpTo(n);
    map<int, bool> primeCache;
    map<int, bool>::iterator cacheIt;
    queue<Candidate> candidates;
    Candidate current;
    int sum = 0, j;


    // O(1) lookup, memory is a non-issue
    for(vector<int>::iterator i = primes.begin(); i != primes.end(); ++i) {
        primeCache[*i] = 1;
    }

    for(int i = 0; sum + primes[i] < n; ++i) {
        sum += primes[i];
        j = i;
    }

    candidates.push((Candidate){sum, 0, j});

    while(!candidates.empty()) {
        current = candidates.front();
        candidates.pop();

        if(primeCache.find(current.value) != primeCache.end()) {
            return current.value;
        } else {

            // We need to keep current.value positive otherwise we can loop
            // forever...
            if(current.first + 1 >= current.last)
                continue;

            candidates.push(
                (Candidate){current.value - primes[current.first],
                            current.first + 1, current.last}
            );
            candidates.push(
                (Candidate){current.value - primes[current.last],
                            current.first, current.last - 1}
            );
        }
    }

    return -1;
}

int main() {
    cout << "The answer is: " << sumOfLongestPrimeSumUnder(1000 * 1000) << endl;
    return 0;
}
