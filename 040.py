'''
ProjectEuler Problem 40

Mikael Fors 2014

"An irrational decimal fraction is created by concatenating the positive
 integers. If dn represents the nth digit of the fractional part, find the value
 of the following expression.

 d1 * d10 * d100 * d1000 * d10000 * d100000 * d1000000"
'''

import operator as op
string = ''.join(str(c) for c in xrange(1, 1000**2 + 1))
print reduce(op.mul, (int(string[i]) 
                        for i in [0, 9, 99, 999, 9999, 99999, 999999]))
