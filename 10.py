'''
ProjectEuler Problem 10

Mikael Fors 2014

"Find the sum of all the primes below two million"
'''
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

print sum(generate_primes_up_to(2 * 1000 ** 2))
