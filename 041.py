'''
ProjectEuler Problem 41

Mikael Fors 2014

"What is the largest n-digit pandigital prime that exists?"
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


# 3 | digital_sum(n) --> 3 | n --> n composite
#
# The largest possible candidate is 987654321, so numlen is 1-9, ensuring that
# the digital sums considered are the 1-9th triangle numbers.
#
#       n        1  2  3  4   5   6   7   8   9
#       tri_n    1  3  6  10  15  21  28  36  45
#       3|          X  X      X   X       X   X
#
# We are left with numlen 7 as the most likely potential max target

# O(1) amort lookup...
primes = {prime:True for prime in generate_primes_up_to(7654322)}
digits = '1234567'

for n in xrange(7654321, 1234567, -2):
    if n not in primes:
        continue
    m, count = str(n), 0
    for digit in digits[:len(m)]:
        k = m.count(digit)
        if k == 1:
            count += 1
        else:
            break
    if count != len(m):
        continue
    print n
    break
