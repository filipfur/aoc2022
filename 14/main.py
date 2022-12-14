import sys
from matplotlib import pyplot

class Particle:
    def __init__(self, x, y):
        self.x = x
        self.y = y
        self.active = True

    def update(self, grid):
        if not self.active:
            return
        if grid.getTile(self.x, self.y + 1) == None:
            self.y += 1
        elif grid.getTile(self.x - 1, self.y + 1) == None:
            self.x -= 1
            self.y += 1
        elif grid.getTile(self.x + 1, self.y + 1) == None:
            self.x += 1
            self.y += 1
        else:
            grid.setTile(self.x, self.y, 'o')
            self.active = False


class Grid:

    def __init__(self):
        self.min=[9999999,9999999]
        self.max=[-100,-100]
        self.tiles = {}

    def setTile(self, x, y, c, updateminmax=True):
        if updateminmax:
            self.min[0] = min(self.min[0], int(x))
            self.min[1] = min(self.min[1], int(y))
            self.max[0] = max(self.max[0], int(x))
            self.max[1] = max(self.max[1], int(y))
        if not y in self.tiles:
            self.tiles[y] = {}
        self.tiles[y][x] = c

    def placeSegment(self, segment):
        for i, pt in enumerate(segment):
            if i == 0:
                continue
            prev = segment[i - 1]
            delta = [pt[0] - prev[0], pt[1] - prev[1]]
            if delta[0] != 0:
                delta[0] /= abs(delta[0])
            if delta[1] != 0:
                delta[1] /= abs(delta[1])
            cur = [prev[0], prev[1]]
            while cur[0] != pt[0] or cur[1] != pt[1]:
                self.setTile(cur[0], cur[1], '#')
                cur[0] += delta[0]
                cur[1] += delta[1]
            self.setTile(cur[0], cur[1], '#')

    def getTile(self, x, y):
        if not y in self.tiles:
            return None
        elif not x in self.tiles[y]:
            return None
        else:
            return self.tiles[y][x]

    def doPrint(self):
        output = ""
        for y in range(self.min[1] - 1, self.max[1] + 2):
            for x in range(self.min[0] - 1, self.max[0] + 2):
                tile = self.getTile(x, y)
                output += ('.' if tile == None else tile)
            output += "\n"
        print(output)

#499,0 -> 499,-1 -> 501,-1 -> 501,0

grid = Grid()
segments = []
for line in sys.stdin:
    line = line.strip()
    arr = [ [int(x) for x in el.split(",")] for el in line.split(" -> ") ]
    print(arr)
    grid.placeSegment(arr)
    segments.append(arr)
    
grid.doPrint()

particles = []


#pyplot.ion()


pyplot.gca().invert_yaxis()

for seg in segments:
    x = [e[0] for e in seg]
    y = [e[1] for e in seg]
    pyplot.plot(x, y, linewidth=4)

finalLevel = False
lastX = 0
lastY = 0
for i in range(1000000):
    #particles.append(Particle(500, 0))
    #for p in particles:
    #    p.update(grid)
    p = Particle(500, 0)
    particles = [p]
    while p.active:
        p.update(grid)
        if p.y > grid.max[1]:
            lastX = p.x
            lastY = p.y
            break
    if p.y > grid.max[1]:
        if not finalLevel:
            grid.placeSegment([[lastX - 1000, lastY + 1], [lastX + 1000, lastY + 1]])
            print("You unlocked the final level!")
            #grid.doPrint()
            finalLevel = True
        else:
            p = Particle(500,0)
            while p.active:
                p.update(grid)
                grid.setTile(p.x, p.y, "~", False)
                if p.y > grid.max[1]:
                    break
            print("abyss encountered after {} iterations".format(i))
            break
    px = [p.x for p in particles]
    py = [p.y for p in particles]
    pyplot.scatter(px, py, marker='o', s=10)
    if grid.getTile(500, 0) == 'o':
        print("Finally at rest after {} iterations.".format(i))
        break
    #pyplot.pause(0.2)

#grid.doPrint()

#pyplot.show()