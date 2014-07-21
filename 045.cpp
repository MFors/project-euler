/*
  Project Euler Problem 45
  Mikael Fors 2014

  "It can be verified that T_285 = P_165 = H_143 = 40755.

   Find the next triangle number that is also pentagonal and hexagonal."
*/

#include <iostream>
#include <cmath>

int main() {
    /*
        Notice that every odd triangle number is a hexagonal number:

        H_n = T_{2n - 1}

        So we need to find an odd triangle number that is also pentagonal.
        How to check for pentagonal numbers? Well, consider the following:

        m is a pentagonal <=> m = n(3n-1)/2 for some n <=> 3n^2 - n - 2m = 0

        This polynomial of d=2 has a=3, b=-1 and c=2m so its two roots are

        r_0 = (1 + sqrt(1 + 24m)) / 6
        r_1 = (1 - sqrt(1 + 24m)) / 6

        This means that sqrt(1 + 24m) must be congruent to -1 or 5 modulo 6.
        Further, recall that x is a prefect square modulo n if there exists
        a y such that y^2 = x mod n and that xy mod n is the same as (x mod n)
        times (y mod n) mod n.

        We have:

        sqrt(1 + 24m) = 5 mod 6 which means that sqrt(1 + 24m)^2 mod 6 is equal
        to 5 * 5 mod 6 = 25 mod 6 = 1. But, as previously stated, this also means
        that 1 + 24m is a perfect square!

        The case is clear: That m is a pentagonal means two things:

        (i)     1 + 24m is a perfect square
        (ii)    sqrt(1 + 24m) is congruent to 5 mod 6

        As r_1 hints, if sqrt(1 + 24m) = 1 mod 6, we get r_1 = 0 mod 6 which
        is no difference from r_0 if sqrt(1 + 24m) is 5 mod 6, i.e. both roots
        will yield a value that is congruent to 0 mod 6.

    */

    // For reference, the intermediary value for triangle overflows int during
    // calculations
    long result = 0, triangle;
    double side;

    for(long n = 287; !result; n += 2) {
        triangle = (n * (n + 1)) >> 1;
        side = std::sqrt(1 + 24 * triangle);
        result = side == long(side) && long(side) % 6 == 5 ? triangle : 0;
    }

    std::cout << "The answer is " << result << std::endl;
    return 0;
}
