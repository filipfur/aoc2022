import sys

grid = []
for line in sys.stdin:
    row = []
    for i in range(len(line)):
        try:
            row.append(int(line[i]))
        except:
            pass
    grid.append(row)



N = len(grid)
M = len(grid[0])

columnfirst = [[0 for y in grid] for x in grid[0]]

for y, row in enumerate(grid):
    for x, tree in enumerate(row):
        columnfirst[x][y] = tree
    print(row)

print()

#for y, column in enumerate(columnfirst):
#    print(column)

visible = {}

visible = []

viewdistances = []

visiblecount = 0

for i in range(N):
    visible.append([0 for x in range(M)])

for i in range(N):
    viewdistances.append([0 for x in range(M)])

#for row in visible:
#    print(row)

def functionOld():
    for y, row in enumerate(grid[1:-1]):
        max = row[0]
        for x, tree in enumerate(row[1:-1]):
            if tree > max:
                if visible[y][x] == 0:
                    visiblecount += 1
                visible[y][x] = tree
                max = tree
        max = row[len(row) - 1]
        for x, tree in reversed(list(enumerate(row[1:-1]))):
            if tree > max:
                if visible[y][x] == 0:
                    visiblecount += 1
                visible[y][x] = tree
                max = tree


    for x, column in enumerate(columnfirst[1:-1]):
        max = column[0]
        for y, tree in enumerate(column[1:-1]):
            if tree > max:
                if visible[y][x] == 0:
                    visiblecount += 1
                visible[y][x] = tree
                max = tree
        max = column[len(row) - 1]
        for y, tree in reversed(list(enumerate(column[1:-1]))):
            if tree > max:
                if visible[y][x] == 0:
                    visiblecount += 1
                visible[y][x] = tree
                max = tree

def viewDistanceX(x0, xn, y):
    distance = 0
    if x0 == xn:
        return distance
    delta = 1 if x0 < xn else -1
    #print("checking [{}, {}, {}]".format(x0, xn, delta))
    for x in range(x0 + delta, xn + delta, delta):
        distance += 1
        if grid[y][x] >= grid[y][x0]:
            break
    return distance

def viewDistanceY(y0, yn, x):
    distance = 0
    if y0 == yn:
        return distance
    delta = 1 if y0 < yn else -1
    #print("checking [{}, {}, {}]".format(y0, yn, delta))
    for y in range(y0 + delta, yn + delta, delta):
        #print("checking tree {} >= {}".format(grid[y][x], grid[y0][x]))
        distance += 1
        if grid[y][x] >= grid[y0][x]:
            break
    return distance

maxviewdistance = 0

for y in range(N):
    for x in range(M):
        viewdistances[y][x] = viewDistanceX(x, 0, y) \
            * viewDistanceX(x, M - 1, y) \
            * viewDistanceY(y, 0, x) \
            * viewDistanceY(y, N - 1, x)
        maxviewdistance = max(viewdistances[y][x], maxviewdistance)

visiblecount += (N + M) * 2 - 4

for row in viewdistances:
    print(row)


arr = [1, 2, 3, 4]

for x in range(2, 0, -1):
    print(arr[x])

print("this^")

print("maxviewdistance={}".format(maxviewdistance))
print("visiblecount: {}".format(visiblecount))