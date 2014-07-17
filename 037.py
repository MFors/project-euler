'''
ProjectEuler Problem 37

Mikael Fors 2014

"Find the sum of the only eleven primes that are both truncatable from left to
 right and right to left"
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
        sieve.append(True)
        if 6 * k + 1 <= n:
            sieve.append(True)
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
                sieve[position] = False
                ptr ^= 1

    return [2, 3] + [6 * ((i // 2) + 1) + (-1 if not i & 1 else 1)
                            for i, val in enumerate(sieve) if val]

primes = {prime:True for prime in generate_primes_up_to(10 ** 6)}
result, count = 0, 0

for prime, _ in primes.iteritems():
    if prime < 10:
        continue

    kLeft, kRight, valid = prime, prime, True

    while 1:
        kLeft %= 10 ** (len(str(kLeft)) - 1)
        kRight //= 10
        if not kRight:
            break
        if not kLeft in primes or not kRight in primes:
            valid = False
            break

    result += prime if valid else 0
    count += int(valid)

    if count == 11:
        break

print result
