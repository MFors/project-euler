'''
ProjectEuler Problem 36

Mikael Fors 2014

"Find the sum of all numbers, less than one million, which are palindromic in
 base 10 and base 2."
'''

# 0 and all odds under 10 are trivially palindromes in binary and decimal
# (an even number can never be a binary palindrome unless it is 0)
palindromes = [0] + range(1, 10, 2)

# We then generate all decimal palindromes, which is done by considering
# the strings 10...999 and then merging them with and without overlap
# e.g. 317 yields 317 713 and 31 7 13
for k in xrange(10, 1000):
    m = 10 ** len(str(k))

    # Dual digit are a special case, e.g. 33 which is otherwise missed
    if k < 100 and k // 10 == k % 10 and bin(k)[2:] == bin(k)[2:][::-1]:
        palindromes.append(k)

    for val in [k * m + int(str(k)[::-1]),
                k * m // 10 + int(str(k // 10)[::-1])]:
        if bin(val)[2:] == bin(val)[2:][::-1]:
            palindromes.append(val)

print sum(palindromes)
