'''
ProjectEuler Problem 30

Mikael Fors 2014

"Find the sum of all the numbers that can be written as the sum of fifth powers
 of their digits"
'''

# 9 ** 5 = 59049, so 6 digit is max, 200k is broken at 4 9:s

value = 0
for n in xrange(2, 199000):
    current, m = 0, n
    while m:
        current += (m % 10) ** 5
        m //= 10
    if current == n:
        value += current
print value
