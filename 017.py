'''

ProjectEuler Problem 17

Mikael Fors 2014

"If all the numbers from 1 to 1000 (one thousand) inclusive were written out in
 words, how many letters would be used?"
'''

'''
digits:
3: one, two, six
4: four, five, nine
5: three, seven, eight

teens:
3: ten
6: eleven, twelve
7: fifteen, sixteen
8: thirteen, eighteen, nineteen, fourteen
9: seventeen

tens:
5: forty, fifty, sixty
6: twenty, thirty, eighty, ninety
7: seventy
'''

solution = 0

solution += len("onethousand")
solution += len("hundred") * 900
solution += len("and") * 99 * 9

singleDigits = 3 * (3 + 4 + 5)
teens = 3 + 2 * (6 + 7) + 4 * 8 + 9
tens = 5 * 3 + 6 * 4 + 7

print singleDigits, teens, tens

# digits occur accross each 100 except multiples
# of 10 and teens
solution += singleDigits * 9 * 10
# digits also occur when "k hundred" so each one occurs 100 times
solution += singleDigits * 100

# teens occur once per 100
solution += teens * 10

# tens occur 10 times per 100 for each 100
solution += tens * 10 * 10

print solution
