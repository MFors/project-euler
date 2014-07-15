'''
ProjectEuler Problem 3

Mikael Fors 2014

"What is the largest prime factor of the number 600851475143?"
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


# The largest factor of any composite is its square root
n = 600851475143
m = int(math.sqrt(n))
primes = generate_primes_up_to(m)

# Now go through all primes from largest to smallest
# (primes array is trivially sorted) and find first that divides n
i = len(primes) - 1
while n % primes[i]:
    i -= 1
print primes[i]
