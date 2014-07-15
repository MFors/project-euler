'''
ProjectEuler Problem 15

Mikael Fors 2014

"Starting in the top left corner of a 2×2 grid, and only being able to move to
 the right and down, there are exactly 6 routes to the bottom right corner.

 How many such routes are there through a 20×20 grid?"
'''

# The answer is the number of ways we can place 20 downs in 40 moves.
# This is equivalent to 40 pick 20 and is easy to calculate:

import operator as op
print reduce(op.mul, xrange(21, 41)) // reduce(op.mul, xrange(2, 21))
