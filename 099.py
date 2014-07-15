'''
ProjectEuler Problem 99

Mikael Fors 2014

"How many digit factorial chains, with a starting number below one million,
 contain exactly sixty non-repeating terms?"
'''

import math
with open('099.data', 'r') as raw:
    print max(enumerate(map(int, r.split(',')) for r in raw.readlines() 
              if len(r)), key=lambda row: math.log(row[1][0])*row[1][1])[0] + 1
