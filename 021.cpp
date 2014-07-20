/*
  Project Euler Problem 21
  Mikael Fors 2014

  "Let d(n) be defined as the sum of proper divisors of n. If d(a) = b and d(b)
   = a, where a != b, then a and b are an amicable pair and each of a and b are
   called amicable numbers.

   Evaluate the sum of all the amicable numbers under 10000."
*/

#include <cmath>
#include <iostream>
#include <vector>
#include <map>
#include <boost/dynamic_bitset.hpp>

/* Maybe should make separate helper lib... */
class ProjectEuler {
        std::vector<int> primes;

    public:
        // Primes
        std::vector<int> generatePrimesUpTo(int n);
        void cachePrimesUpTo(int n);

        // Divisors
        std::vector<int> properDivisorsOf(int n);
        int sumOfProperDivisorsOf(int n);

};

std::vector<int> ProjectEuler::generatePrimesUpTo(int n) {
    std::vector<int> primes;

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

void ProjectEuler::cachePrimesUpTo(int n) {
    primes = generatePrimesUpTo(n);
}

std::vector<int> ProjectEuler::properDivisorsOf(int n) {
    std::vector<int> result;
    int arity, divisor, m = n, oldMax;

    if(!primes.size() || *(primes.rbegin()) < int(std::sqrt(n))) {
        cachePrimesUpTo(int(std::sqrt(n)));
    }

    for(std::vector<int>::iterator prime = primes.begin();
        prime != primes.end(); ++prime) {

        arity = 0;

        while(!(m % *prime)) {
            ++arity;
            m /= *prime;
        }

        oldMax = result.end() - result.begin();
        for(int i = 0; i < arity; ++i) {
            divisor = pow(*prime, i + 1);
            if(divisor != n)
                result.push_back(divisor);
            for(int j = 0; j < oldMax; ++j) {
                if(divisor * result[j] < n)
                    result.push_back(divisor * result[j]);
            }
        }
    }
    if(m > 1 && m != n) {
        oldMax = result.end() - result.begin();
        result.push_back(m);
        for(int j = 0; j < oldMax; ++j) {
            if(m * result[j] < n)
                result.push_back(m * result[j]);
        }
    }
    result.push_back(1);
    return result;
}

int ProjectEuler::sumOfProperDivisorsOf(int n) {
    std::vector<int> divisors = properDivisorsOf(n);
    int result = 0;
    for(std::vector<int>::iterator i = divisors.begin();
        i != divisors.end(); ++i) {
            result += *i;
    }
    return result;
}


int main() {
    ProjectEuler euler;
    int t, result = 0;

    for(int i = 4; i < 10000; ++i) {
        t = euler.sumOfProperDivisorsOf(i);
        if(t == i)
            continue;
        result += euler.sumOfProperDivisorsOf(t) == i ? i : 0;
    }
    std::cout << result << std::endl;
    return 0;
}
