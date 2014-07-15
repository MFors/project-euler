'''
ProjectEuler Problem 74

Mikael Fors 2014

"How many digit factorial chains, with a starting number below one million,
 contain exactly sixty non-repeating terms?"
'''

import operator as op

# Can be improved by caching intermediaries in the chains also,
# but that requires us to keep track of chain order...

def factorial(n):
    return reduce(op.mul, xrange(1, n + 1))

factorials = {x:factorial(x) for x in xrange(1, 10)}
factorials[0] = 1

count, superCache = 0, {}

for n in xrange(2, 1000000):
    m = n
    cache = {}
    while 1:
        if m in superCache:
            val = len(cache) + superCache[m]
            superCache[n] = val
            count += int(val == 59)
            break
        s = 0
        while m:
            t = m % 10
            m //= 10
            s += factorials[t]
        m = s
        if m in cache:
            count += int(len(cache) == 59)
            superCache[n] = len(cache)
            break
        else:
            cache[m] = True

print count        
