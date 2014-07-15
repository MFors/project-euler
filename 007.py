'''
ProjectEuler Problem 7

Mikael Fors 2014

"What is the 10 001st prime number?"
'''
import math

# Slightly optimized sieve where we disregard all numbers not on the form
# 6k +/- 1 and thus reduce memory requirements a bit
def generate_primes_up_to(n):
    # Handle trivial cases
    if n < 2:
        return []
    if n < 5:
        return [2] if n < 3 else [2, 3]

    primes = [2, 3]
    sieve = []
    k = 1

    # Make the sieve
    while 6 * k - 1 <= n:
        sieve.append(1)
        if 6 * k + 1 <= n:
            sieve.append(1)
        k += 1

    # Remove all non-primes
    for i, val in enumerate(sieve):
        if val:
            #   -> The offset translates i to "k" in 6k +/- 1
            #   -> i & 1 will indicate + 1

            #   Multiples of sieve[i] follow a simple pattern, namely:
            #   value + 2 * offset, value - 2 * offset, value + 2 * offset, ...
            offset = (i // 2) + 1
            value = 6 * offset + (-1 if not i & 1 else 1)
            jump = (value + 2 * offset, value - 2 * offset)
            ptr = 0
            position = i
            while position + jump[ptr] < len(sieve):
                position += jump[ptr]
                sieve[position] = 0
                ptr ^= 1

    return [2, 3] + [6 * ((i // 2) + 1) + (-1 if not i & 1 else 1) 
                            for i, val in enumerate(sieve) if val]


# To generate no 10001, we can estimate our search space using the fact that
# there are about n / log_10(n) primes in [1, n]
n, k = 10001, 4 * n
while k / math.log(k) < n:
    k += n # The += n portion is obviously not great if n is large!
print generate_primes_up_to(k)[n - 1]
