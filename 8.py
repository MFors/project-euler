'''
ProjectEuler Problem 8

Mikael Fors 2014

"Find the thirteen adjacent digits in the 1000-digit number that have the
 greatest product. What is the value of this product?"
'''

# This problem can be solved in O(n) by keeping two pointers and moving the
# first, multiplying the product with the new value and dividing it with the
# value at the last pointer
#
# a b c d e f
# L       F               Let ++F, then
#
# a b c d e f
# L         F             abcde *= f, abcdef //= a, ++L
#
# a b c d e f             ... and so forth...
#   L       F
#
# However, since moving to a zero requires us to "shift" the pointers until
# their difference is equivalent to the required number of factors, it becomes
# a lot of work for such a small number (1000-digits).
#
# Due to its simplicity, we use a O(n^2) approach where we need to reduce a
# subarray (O(n)) kn times (O(n)).

import operator as op
with open('8.data', 'r') as raw:
    data, maximum = map(int, (c for c in raw.read())), 0
    for i in xrange(len(data) - 13):
        maximum = max(maximum, reduce(op.mul, data[i:i+13]))
    print maximum
