'''
ProjectEuler Problem 1

Mikael Fors 2014

"Find the sum of all the multiples of 3 or 5 below 1000."
'''
# An efficient way is to note that there are 999//5 multiples of 5
# and this means that there are in total t_{999//5} counts, resulting in
# a sum of (999//5 ** 2 + 999//5) >> 1

# The same can then be done for 3, we add these together and remove the multiples
# of 15

triangle = lambda n: (n ** 2 + n) >> 1
print triangle(999//3) * 3 + triangle(999//5) * 5 - triangle(999//15) * 15
