/*
  Project Euler Problem 24
  Mikael Fors 2014

  "What is the millionth lexicographic permutation of the digits 0, 1, 2, 3, 4,
   5, 6, 7, 8 and 9?"
*/

#include <iostream>

int factorial(int n) {
    if (n < 1)
        return 1;
    int result = n;
    while(--n) {
        result *= n;
    }
    return result;
}

int main() {
    /*

        By calculating the number of permutations for each digit placement,
        i.e. 123 would have 1*2*3 for placement digit '1' and so forth,
        we can easily calculate how many "cycles" is needed per digit
        placement. We keep doing this for each digit placement until we
        reach the desired result.

        The outcome cycle tells us how many switches need to be made from
        available digits, meaning cycle=2 would yield 3 if 1 has already been
        used.

        It is important to note that the target is 999999 rather than 1000000
        since the first lexical permutation is given by the trivial string
        0123456789.

    */
    int target = 1000 * 1000 - 1, factorials[10],
        currentFactIndex = 9, cycle = 0, count = 0;

    for (int i = 0; i < 10; ++i)
        factorials[i] = factorial(i);

    bool used[10];
    long answer = 0L;

    while (target) {
        cycle = target / double(factorials[currentFactIndex]);
        target -= cycle * factorials[currentFactIndex];
        answer *= 10;
        --currentFactIndex;

        count = 0;
        for (int i = 0; i < 10; ++i) {
            if (!used[i]) {
                if (count == cycle) {
                    answer += i;
                    used[i] = true;
                    break;
                }
                ++count;
            }
        }
    }

    count = 0;
    for (int i = 0; i < 10; ++i) {
        if (!used[i]) {
            answer *= 10;
            answer += count;
            ++count;
        }
    }

    std::cout << "The answer is: " << answer << std::endl;
    return 0;
}
