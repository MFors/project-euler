'''
ProjectEuler Problem 27

Mikael Fors 2014

"Find the product of the coefficients, a and b, for the quadratic expression
 that produces the maximum number of primes for consecutive values of n,
 starting with n = 0"
'''

def generate_primes_up_to(n):
    if n < 2:
        return []
    if n < 5:
        return [2] if n < 3 else [2, 3]

    primes = [2, 3]
    sieve = []
    k = 1

    while 6 * k - 1 <= n:
        sieve.append(1)
        if 6 * k + 1 <= n:
            sieve.append(1)
        k += 1

    for i, val in enumerate(sieve):
        if val:
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


primes = generate_primes_up_to(997)
maxCount, maxProduct = 0, 0

for b in primes:
    for a in xrange(-b, b, 2):
        n, count = 0, 0
        while (n * n + a * n + b) in primes:
            count +=1
            n += 1
        maxCount = max(maxCount, count)
        maxProduct = a * b if maxCount == count else maxProduct

print maxProduct
