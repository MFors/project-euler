'''
ProjectEuler Problem 149

Mikael Fors 2014

"First, generate four million pseudo-random numbers using a specific form of
 what is known as a 'Lagged Fibonacci Generator':

    For 1 <= k <= 55, s_k = [100003 - 200003k + 300007k**3] (modulo 1000000)
     - 500000

    For 56 <= k <= 4000000, s_k = [s_(k-24) + s_(k-55) + 1000000] (modulo
    1000000) - 500000

    Thus, s_10 = -393027 and s_100 = 86613.

 The terms of s are then arranged in a 2000x2000 table, using the first 2000
 numbers to fill the first row (sequentially), the next 2000 numbers to fill
 the second row, and so on.

 Finally, find the greatest sum of (any number of) adjacent entries in any
 direction (horizontal, vertical, diagonal or anti-diagonal)."
'''

mod = 1000 ** 2
table = [[0 for n in xrange(2000)] for row in xrange(2000)]

for k in xrange(1, 4 * mod + 1):
    value = 0
    if k < 56:
        value = 100003
        # For every 5th k, 200003k % mod is 15
        multiple = k // 5
        value -= multiple * 15
        for m in xrange(k - multiple * 5):
            value -= 200003
            value %= mod
        # Now we need to add the 300007k ** 3 part
        # 300007 * 10 % 1000 ** 2 = 70
        k2 = k ** 3
        if k2 > 10:
            multiple = k2 // 10
            k2 -= (multiple * 10)
            value += 70 * multiple
        for m in xrange(k2):
            value += 300007
            value %= mod
        value -= 500000
    else:
        # Careful with offset (k=1 -> [0][0])
        k24, k55 = k - 25, k - 56
        value = table[k24 // 2000][k24 % 2000]
        value += table[k55 // 2000][k55 % 2000]
        value %= mod
        value -= 500000
    table[(k - 1) // 2000][(k - 1) % 2000] = value


maxVal = 0
maxSet = 0 # Due to value range, max may be 0 or negative

# Store as (hori, verti, dia-right, dia-left)
for row in xrange(2000):
    for col in xrange(2000):

        hori = table[row][col] if not col else max(table[row][col],
                         table[row][col] + table[row][col-1][0])

        verti = table[row][col] if not row else max(table[row][col],
                         table[row][col] + table[row-1][col][1])

        diaR = table[row][col] if not row or not col else max(table[row][col],
                         table[row][col] + table[row-1][col - 1][2])

        diaL =table[row][col] if not row or col == 1999 else max(table[row][col],
                         table[row][col] + table[row-1][col + 1][3])

        table[row][col] = (hori, verti, diaR, diaL)
        currentMax = max(hori, verti, diaR, diaL)

        maxVal = currentMax if not maxSet else max(maxVal, currentMax)
        maxSet = 1

print maxVal
