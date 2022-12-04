import sys;

badCouples = 0
totalLines = 0

def containedby(data):
    return data[0][0] <= data[1][0] and data[0][1] >= data[1][1] or data[1][0] <= data[0][0] and data[1][1] >= data[0][1]

def overlaps(data):
    if data[0][0] < data[1][0]:
        return data[0][1] >= data[1][0]
    elif data[0][0] > data[1][0]:
        return data[1][1] >= data[0][0]
    else:
        return True

for line in sys.stdin:
    #data = [[a for a in range(int(y[0]), int(y[1]) + 1)] for y in [x.split('-') for x in line.split(',')]]
    data = [[int(y[0]), int(y[1])] for y in [x.split('-') for x in line.split(',')]]
    #if containedby(data):
    if overlaps(data):
        badCouples += 1
    print(data)
    totalLines += 1

print(f"badCouples={badCouples}, totalLines={totalLines}")