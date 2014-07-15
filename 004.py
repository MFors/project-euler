'''
ProjectEuler Problem 4

Mikael Fors 2014

"Find the largest palindrome made from the product of two 3-digit numbers."
'''
print max((a * b for a in xrange(999, 990, -1) for b in xrange(999, 800, -1)
                                         if str(a * b)[::-1] == str(a * b)))
