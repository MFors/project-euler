'''
ProjectEuler Problem 9

Mikael Fors 2014

"There exists exactly one Pythagorean triplet for which a + b + c = 1000.
 Find the product abc"
'''

# a can at most be 332
# b can at most be (332 + 333) - a
# c will then always be at least 335

answer = 0
for a in xrange(1, 332 + 1):
    for b in xrange(a + 1, 665 - a):
        c = 1000 - (a + b)
        if a ** 2 + b ** 2 == c ** 2:
            answer = a * b * c
            break
    if answer:
        break
print answer
