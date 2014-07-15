'''
ProjectEuler Problem 14

Mikael Fors 2014

"Which starting number, under one million, produces the longest Collatz chain?"
'''

# Cache previous chains for extra speed
cache = {}
funcs = [lambda n: n >> 1, lambda n: 3 * n + 1]

for n in xrange(1, 1000 ** 2):
    count, m = 0, n
    while n != 1:
        n = funcs[n & 1](n)
        count += 1
        if n in cache:
            count += cache[n]
            break
    cache[m] = count

maximum, maxKey = 0, -1

for key, val in cache.iteritems():
    if val > maximum:
        maximum = val
        maxKey = key
print maxKey
