#include <iostream>
#include <vector>
#include <map>

#include "../lib/vec2.h"

static constexpr int X{81};
static constexpr int Y{41};

struct Node
{
    Vec2 pos;
    std::vector<Node*> neighbours;
    std::map<int,std::map<int, bool>> visited;
    Node* parent{nullptr};

    void setVisited(Node* node)
    {
        visited[node->pos.y][node->pos.x] = true;
    }

    bool hasVisited(int x, int y)
    {
        auto it = visited.find(y);
        if(it != visited.end())
        {
            auto it2 = it->second.find(x);
            if(it2 != it->second.end())
            {
                return it2->second;
            }
        }
        return false;
    }
};

Vec2 start{};
Vec2 end{};
int grid[Y][X]; // elevation

int bestLevel = INT_MAX;
Node* bestNode{nullptr};
Node* root;

int gridHeight(int x, int y)
{
    if(x < 0 || x >= X || y < 0 || y >= Y)
    {
        return 999999;
    }
    return grid[y][x];
}

int setNeighbours(Node* node, int level)
{
    int curHeight = gridHeight(node->pos.x, node->pos.y);
    int rval = INT_MAX;
    static const Vec2 deltas[] = {
        Vec2{0,1},
        Vec2{0,-1},
        Vec2{-1, 0},
        Vec2{1, 0}
    };
    for(Vec2 delta : deltas)
    {
        int xx = node->pos.x + delta.x;
        int yy = node->pos.y + delta.y;
        if(node->hasVisited(xx, yy)) // Don't go back.
        {
            continue;
        }
        int height = gridHeight(xx, yy);
        if(height < curHeight + 2)
        {
            auto child = new Node();
            //std::cout << "traveling d.x=" << delta.x << ", d.y=" << delta.y << std::endl;
            child->pos.x = xx;
            child->pos.y = yy;
            //std::copy(node->visited.begin(), node->visited.end(), child->visited.begin());
            child->visited = node->visited;
            /*for(auto map : node->visited)
            {
                for(auto b : map.second)
                {
                    child->visited[map.first][b.first] = b.second;
                }
            }*/
            child->parent = node;
            child->setVisited(node);
            if(end.x == xx && end.y == yy)
            {
                Node* n = child;
                int steps = 0;
                while(n)
                {
                    ++steps;
                    n = n->parent;
                }

                if(steps < bestLevel)
                {
                    std::cout << "Reached end point: " << end.x << ", " << end.y << ", " << steps << std::endl;
                    bestNode = child;
                    bestLevel = steps;
                }
                //Node * n = child;
                //while(n)
                
                rval = std::min(level, rval);
            }
            else
            {
                rval = std::min(rval, setNeighbours(child, level + 1));
            }
        }
    }
    return rval;
}

int main(int argc, const char* argv[])
{
    char c;
    int i{0};
    int j{0};
    while(std::cin >> c)
    {
        if(c == 'S')
        {
            c = 'a';
            start.x = i;
            start.y = j;
        }
        else if(c == 'E')
        {
            c = 'z';
            end.x = i;
            end.y = j;
        }
        grid[j][i] = static_cast<int>(c);
        
        if(std::cin.peek() == '\n')
        {
            //std::cout << i << std::endl;
            i = 0;

            ++j;
        }
        else
        {
            ++i;
        }
    }

    //std::cout << "j" << j << std::endl;
    //exit(0);

    std::cout << "start: " << start.x << ", " << start.y << std::endl;
    std::cout << "end: " << end.x << ", " << end.y << std::endl;

    root = new Node();
    root->pos = start;

    int steps = setNeighbours(root, 0);
    std::cout << "steps: " << steps << std::endl;

    char visualGrid[Y][X];
    memset(visualGrid, '.', X * Y);
    steps = 0;
    if(bestNode != nullptr)
    {
        Node* node = bestNode;
        Node* prev {nullptr};
        //Node* e = new Node();
        //e->pos = end;
        //prev = e;
        while(node)
        {
            char c = '#';
            if(prev)
            {
                //Vec2 delta = //(prev->pos - node->pos);
                Vec2 delta = prev->pos;
                delta -= node->pos;
                if(delta.x > 0)
                {
                    c = '>';
                }
                else if(delta.x < 0)
                {
                    c = '<';
                }
                else if(delta.y > 0)
                {
                    c = 'v';
                }
                else if(delta.y < 0)
                {
                    c = '^';
                }
            }
            visualGrid[node->pos.y][node->pos.x] = c;
            prev = node;
            node = node->parent;
            ++steps;
        }
        visualGrid[end.y][end.x] = 'E';

    }


    for(int y{0}; y < Y; ++y)
    {
        for(int x{0}; x < X; ++x)
        {
            std::cout << ' ' << static_cast<char>(grid[y][x]);
        }
        std::cout << std::endl;
    }

    std::cout << "actual: " << steps << std::endl;

    for(int y{0}; y < Y; ++y)
    {
        for(int x{0}; x < X; ++x)
        {
            std::cout << ' ' << visualGrid[y][x];
        }
        std::cout << std::endl;
    }

    return 0;
}