'''
ProjectEuler Problem 16

Mikael Fors 2014

"What is the sum of the digits of the number 2 ** 1000?"
'''
print sum(int(c) for c in str(2 << 999))
