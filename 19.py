'''
ProjectEuler Problem 19

Mikael Fors 2014

"How many Sundays fell on the first of the month during the twentieth century
(1 Jan 1901 to 31 Dec 2000)?"
'''

regularDaysPerMonth = {k : (30 if k in [4, 6, 9, 11] else 31)
                            for k in xrange(1, 13)}
regularDaysPerMonth[2] = 28

# Identify leap-years and return accurate no. of days in feb
def days_in_month(m, y):
    if y % 4 or (not y % 100 and y % 400):
        return regularDaysPerMonth[m]
    else:
        return regularDaysPerMonth[m] if m != 2 else 29


# Start the count. Note that we start the loop at 1900 since we know that
# 1 Jan 1900 was a Monday, but the actual count starts from 1901!
day, count = 0, 0
for year in xrange(1900, 2001):
    for month in xrange(1, 13):
        count += int(day == 6) if year > 1900 else 0
        day += days_in_month(month, year)
        day %= 7
print count
