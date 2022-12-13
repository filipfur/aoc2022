import sys;
import json;
import functools

left=[]
right=[]
sumIndices = 0
i = 0
for line in sys.stdin:
    if i % 3 == 0:
        left.append(json.loads(line.strip()))
    if i % 3 == 1:
        right.append(json.loads(line.strip()))
    i += 1

def listify(left, right):
    
    N = min(len(left), len(right))
    for i in range(N):
        if type(left[i]) != type(right[i]):
            if type(left[i]) == int:
                left[i] = [left[i]]
                listify(left[i], right[i])
            else:
                right[i] = [right[i]]
                listify(left[i], right[i])
        elif type(left[i]) == list:
            listify(left[i], right[i])
    #if type(left[x]) != type(right[x]):
    #    if type(left[i][j]) == int:
    #        left[x] = [left]
    #    if type(right[i][j]) == int:
    #        right[i][j] = [right[i][j]]

def skip():
    for i in range(len(left)):
        result = 1
        for j in range(len(left[i])):
            if j >= len(right[i]):
                result = -1
                break
            print(f"  - Compare {left[i][j]} vs {right[i][j]}")
            listify(left[i], right[i])
            if left[i][j] < right[i][j]:
                result = 1
                break
            if left[i][j] > right[i][j]:
                result = -1
                break

        if result == 1:
            print("    - right order")
            sumIndices += i + 1
        elif result == -1:
            print("    - wrong order")


packets = left + right + [[2]] + [[6]]

def cmp_packets(left, right):
    result = -1
    for j in range(len(left)):
        if j >= len(right):
            result = 1
            break
        #print(f"  - Compare {left[j]} vs {right[j]}")
        listify(left, right)
        if left[j] < right[j]:
            result = -1
            break
        if left[j] > right[j]:
            result = 1
            break
    return result

packets = sorted(packets, key=functools.cmp_to_key(cmp_packets))

for i, packet in enumerate(packets):
    if str(packet) == "[[[[2]]]]" or str(packet) == "[[[[6]]]]":
        print(f"      {str(packet)}={i + 1}")
    #print(packet)

print(f"sum indices={sumIndices}")