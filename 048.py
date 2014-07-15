'''
ProjectEuler Problem 48

Mikael Fors 2014

"Find the last ten digits of the series, 1 ** 1 + 2 ** 2 + 3 ** 3 + ... +
 1000 ** 1000."
'''

result = 1
for n in xrange(2, 1001):
    m = n
    for i in xrange(n - 1):
        m *= n
        m %= 10000000000
    result += m
    result %= 10000000000

print result
