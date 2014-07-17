'''
ProjectEuler Problem 35

Mikael Fors 2014

"How many circular primes are there below one million?"
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

count = 4 # 2, 3, 5, 7

for prime, _ in primes.iteritems():
    k = prime
    while 1:
        r = k % 10
        k /= 10
        r *= 10 ** len(str(k))
        k += r
        if k == prime:
            count += 1
            break
        if k not in primes:
            break

print count
