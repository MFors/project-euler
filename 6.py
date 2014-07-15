'''
ProjectEuler Problem 6

Mikael Fors 2014

"Find the difference between the sum of the squares of the first one hundred
 natural numbers and the square of the sum."
'''
def sqr_difference(n):
    return ((n ** 2 + n) // 2) ** 2 - int((n / 6.0) * (n + 1) * ((n << 1) + 1))
print sqr_difference(100)
