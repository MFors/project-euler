'''
ProjectEuler Problem 67

Mikael Fors 2014

"Find the maximum total from top to bottom in triangle.txt, a 15K text file
 containing a triangle with one-hundred rows."
'''

with open('67.data', 'r') as raw:
    data = raw.read().split('\n')
    data = [map(int, row.split()) for row in data if len(row)]

    # Add through the pyramid
    for row in xrange(1, len(data)):
        for position in xrange(len(data[row])):
            if not position or position == row:
                data[row][position] += data[row-1][position - 1 if position
                                                                else 0]
            else:
                data[row][position] += max(data[row-1][position - 1],
                                           data[row-1][position])

    print max(data[len(data) - 1])
