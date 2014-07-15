'''
ProjectEuler Problem 99

Mikael Fors 2014

"Using base_exp.txt, a 22K text file containing one thousand lines with a
 base/exponent pair on each line, determine which line number has the greatest
 numerical value."
'''

import math
with open('099.data', 'r') as raw:
    print max(enumerate(map(int, r.split(',')) for r in raw.readlines() 
              if len(r)), key=lambda row: math.log(row[1][0])*row[1][1])[0] + 1
