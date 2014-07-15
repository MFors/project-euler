'''
ProjectEuler Problem 12

Mikael Fors 2014

"What is the value of the first triangle number to have over five hundred
 divisors?"
'''

class TriangleChain(object):
    def __init__(self, n=0):
        self.value = 1 if not n else sum((xrange(1, n + 1)))
        self.c = n if n else 1
    def next(self):
        self.c += 1
        self.value += self.c
        return self.value
    def __str__(self):
        return str(self.value)


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


cache, primes = {}, generate_primes_up_to(200000)

def factors(n):
    # Generate prime factors
    pfactors, m = [], n
    for p in primes:
        if n == 1:
            break
        if n in cache:
            pfactors += cache[n]
            break
        while not n % p:
            n //= p
            pfactors.append(p)
    cache[m] = pfactors

    # Let composite C = p_0^a_0 * ... * p_n^a_n, then d s.t. d | C
    # is a selection (k_0, ..., k_n) where 0 <= k_0 <= a_0.
    #
    # This makes it easy to generate the number of divisors, since we have
    # exactly a_0 + 1 ways to pick p_0 (0 and the a_0 arity).
    if not len(pfactors):
        return 2
    i, result = 0, 1
    while i < len(pfactors):
        arity = 2
        while i + 1 < len(pfactors) and pfactors[i] == pfactors[i + 1]:
            arity += 1
            i += 1
        i += 1
        result *= arity
    return result


# 28 had 6 divisors and is the 7th triangle number
triangle = TriangleChain(7)
while 1:
    if factors(triangle.next()) > 500:
        break    
print triangle
