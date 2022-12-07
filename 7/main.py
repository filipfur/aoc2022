import sys

class INode:
    def __init__(self, label, parent, size=0):
        self.label = label
        self.children = {}
        self.parent = parent
        self.size = size

    def add(self, child):
        self.children[child.label] = child

    def sum(self):
        totalsize = self.size
        for child in self.children:
            totalsize += self.children[child].sum()
        if totalsize > 100000:
            totalsize = 0
        return totalsize

    def print(self, indent):
        print(indent + self.label + ("" if self.size == 0 else f" ({self.size})"))
        for child in self.children:
            self.children[child].print(indent + "  ")

command = None
argument = None
root = INode("", None)
inode = root
readfiles = False

sumsizes = 0

for line in sys.stdin:
    arr = line.split()
    if readfiles and arr[0] != "$":
        filesize = int(arr[1])
        sumsizes += filesize
        inode.add(INode(arr[0], inode, filesize))
        continue
    command = arr[1]
    readfiles = False
    argument = None if len(arr) < 3 else arr[2]
    if command == "cd":
        if argument == "..":
            inode = inode.parent
        else:
            tmp = INode(argument, inode)
            inode.add(tmp)
            inode = tmp
    elif command == "ls":
        readfiles = True


root.print("")

print(f"root.sum(): {root.sum()}")
print(sumsizes)