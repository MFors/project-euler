'''
ProjectEuler Problem 2

Mikael Fors 2014

"By considering the terms in the Fibonacci sequence whose values do not exceed
 four million, find the sum of the even-valued terms."
'''
cache, result, ptr, MAX = [1, 2], 2, 0, 4 * 1000 ** 2

while cache[0] <= MAX and cache[1] <= MAX:
    cache[ptr] = sum(cache)
    result += cache[ptr] if not cache[ptr] & 1 else 0
    ptr ^= 1

print result
