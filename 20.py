'''
ProjectEuler Problem 20

Mikael Fors 2014

"Find the sum of the digits in the number 100!"
'''

import operator as op
print sum(int(c) for c in str(reduce(op.mul, xrange(2, 101))))
