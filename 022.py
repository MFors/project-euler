'''
ProjectEuler Problem 22

Mikael Fors 2014

"Using names.txt, a 46K text file containing over five-thousand first names,
 begin by sorting it into alphabetical order. Then working out the alphabetical
 value for each name, multiply this value by its alphabetical position in the
 list to obtain a name score.

 What is the total of all the name scores in the file?"
'''

import re

with open('022.data', 'r') as raw:
    data = re.sub('\n|\"', '', raw.read()).split(',')
    data.sort()
    result = 0
    for i, name in enumerate(data):
        result += (i + 1) * sum(ord(c) - 64 for c in name)
    print result
