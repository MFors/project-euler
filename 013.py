'''
ProjectEuler Problem 13

Mikael Fors 2014

"Work out the first ten digits of the sum of the following one-hundred 50-digit
 numbers."
'''
with open('013.data', 'r') as raw:
    print str(sum(map(int, raw.read().split('\n'))))[:10]
