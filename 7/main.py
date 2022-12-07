import sys

sumsum = 0

directories = []

class INode:
    def __init__(self, label, parent, type, size=0):
        self.label = label
        self.children = {}
        self.parent = parent
        self.size = size
        self.type = type

    def add(self, child):
        self.children[child.label] = child

    def sum(self):
        global sumsum, directories
        totalsize = self.size
        for child in self.children:
            totalsize += self.children[child].sum()
        #if totalsize > 100000:
        #    totalsize = 0
        if self.type == "d":
            if totalsize <= 100000:
                print(self.label + ": {}".format(totalsize))
                sumsum += totalsize
            directories.append((totalsize, self.label))
        return totalsize

    def print(self, indent):
        global directories
        if self.type == "d":
            sum = self.sum()
            print(indent + self.label + " ({})".format(sum))
            directories.append((sum, self.label))
        for child in self.children:
            self.children[child].print(indent + "  ")

command = None
argument = None
root = None
inode = None
readfiles = False

sumsizes = 0

for line in sys.stdin:
    arr = line.split()
    if readfiles and arr[0] != "$":
        filesize = 0 if arr[0] == "dir" else int(arr[0])
        sumsizes += filesize
        inode.add(INode(arr[1], inode, "d" if arr[0] == "dir" else "f", filesize))
        continue
    command = arr[1]
    readfiles = False
    argument = None if len(arr) < 3 else arr[2]
    if command == "cd":
        if argument == "..":
            inode = inode.parent
        elif argument == "/":
            root = INode("", None, "d")
            inode = root
        else:
            inode = inode.children[argument]
            #tmp = INode(argument, inode)
            #inode.add(tmp)
            #inode = tmp
    elif command == "ls":
        readfiles = True


#root.print("")

#sumofall = 46728267
# 70 MB 30 MB
#exit(0)
#
sumofall = root.sum()
print("root.sum(): {}".format(sumofall))
print(sumsizes)
print("sumsum: {}".format(sumsum))
print("START")

available = 70000000 - sumofall
print("available: {}".format(available))
directories.sort()
for tup in directories:
    if tup[0] >= 30000000 - available:
        #print(sumofall - tup[0])
        print("{}: {}".format(tup[1], tup[0]))
        print("this^")
        break