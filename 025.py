'''
ProjectEuler Problem 25

Mikael Fors 2014

"What is the first term in the Fibonacci sequence to contain 1000 digits?"
'''

# Keep two latest numbers in memory, just need to be
# careful with XOR on conditional since it is switched in loop...

fib, ptr, count = [1, 1], 0, 2
while len(str(fib[ptr ^ 1])) < 1000:
    fib[ptr] = sum(fib)
    ptr ^= 1
    count += 1
print count
