/*
  Project Euler Problem 34
  Mikael Fors 2014
  
  "Find the sum of all numbers which are equal to the sum of the
   factorial of their digits"

*/

#include <iostream>
#include <cmath>
using namespace std;

int main() {

    int d2fact[10], currentSum, k, result, len;

    // Cache factorials (only 10 values)
    result = 1, d2fact[0] = 1;
    for(int i = 1; i < 11; ++i) {
        result *= i;
        d2fact[i] = result;
    }
    result = 0;

    // 10 ^ log(n) <= n*9!log(n) for valid n, and delta 10 ^ log(n) > delta n * 9!log(n)
    // for n >= k, means we just have to find smallest such k.
    len = 2;
    while(pow(10, len) < d2fact[9] * len) {
        ++len;
    }

    for(int i = 11; i < pow(10, len - 1); ++i) {
        currentSum = 0;
        k = i;
        while(k) {
            currentSum += d2fact[k % 10];
            k /= 10;
        }
        result += currentSum == i ? i : 0;
    }
    cout << "The answer is: " << result << "\n";
    return 0;
}
