'''
ProjectEuler Problem 11

Mikael Fors 2014

"What is the greatest product of four adjacent numbers in the same direction
 (up, down, left, right, or diagonally) in the 20x20 grid?"
'''

import operator as op

with open('011.data', 'r') as raw:
    data = [map(int, row.split()) for row in raw.read().split('\n') if len(row)]
    maxProduct = 0
    for row in xrange(20):
        for col in xrange(20):
            # horizontal
            if col < 20 - 3:
                maxProduct = max(maxProduct,
                    reduce(op.mul, data[row][col:col + 3]))
            # vertical
            if row < 20 - 3:
                maxProduct = max(maxProduct,
                    data[row][col]
                    * data[row + 1][col]
                    * data[row + 2][col]
                    * data[row + 3][col])
            # right-diagonal
            if row < 20 - 3 and col < 20 - 3:
                maxProduct = max(maxProduct,
                    data[row][col]
                    * data[row + 1][col + 1]
                    * data[row + 2][col + 1]
                    * data[row + 3][col + 1])
            # left-diagonal
            if row < 20 - 3 and col > 2:
                maxProduct = max(maxProduct,
                    data[row][col]
                    * data[row + 1][col - 1]
                    * data[row + 2][col - 2]
                    * data[row + 3][col - 3])
    print maxProduct
