#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <queue>
#include <set>

#include "../lib/vec2.h"

static constexpr int X{81};
static constexpr int Y{41};

//static constexpr int X{8};
//static constexpr int Y{5};

struct Node
{
    Vec2 pos;
    Node* parent{nullptr};
};

std::vector<Vec2> start;
Vec2 end{};
int grid[Y][X]; // elevation

int fewestSteps{999999999};

int bestLevel = 999999999;
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


int main(int argc, const char* argv[])
{
    char c;
    int i{0};
    int j{0};
    while(std::cin >> c)
    {
        if(c == 'S' || c == 'a')
        {
            c = 'a';
            Vec2 s;
            s.x = i;
            s.y = j;
            start.push_back(s);
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
            std::cout << i << std::endl;
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

    std::cout << "start: ";
    std::for_each(start.begin(), start.end(), [](Vec2 start){
        std::cout << " {" << start.x << ", " << start.y << "}";
    });
    std::cout << std::endl;
    std::cout << "end: " << end.x << ", " << end.y << std::endl;

    //return 0;
    for(Vec2 s : start)
    {
    root = new Node();
    root->pos = s;


    /*
 1  procedure BFS(G, root) is
 2      let Q be a queue
 3      label root as explored
 4      Q.enqueue(root)
 5      while Q is not empty do
 6          v := Q.dequeue()
 7          if v is the goal then
 8              return v
 9          for all edges from v to w in G.adjacentEdges(v) do
10              if w is not labeled as explored then
11                  label w as explored
12                  w.parent := v
13                  Q.enqueue(w)
    */

    bestNode = nullptr;
    std::map<int, std::map<int, bool>> explored;
    std::queue<Node*> Q;
    std::set<Node*> allNodes;
    Q.emplace(root);
    explored[root->pos.y][root->pos.x] = true;
    while(!Q.empty())
    {
        Node* v = Q.front();
        allNodes.emplace(v);
        Q.pop();
        int curHeight = gridHeight(v->pos.x, v->pos.y);
        if(v->pos.x == end.x && v->pos.y == end.y)
        {
            bestNode = v;
            //std::cout << "BEST NODE: " << std::endl;
            break;
        }
        static const Vec2 deltas[] = {
            Vec2{0,1},
            Vec2{0,-1},
            Vec2{-1, 0},
            Vec2{1, 0}
        };
        for(Vec2 delta : deltas)
        {
            int xx = v->pos.x + delta.x;
            int yy = v->pos.y + delta.y;
            auto it = explored.find(yy);
            if(it != explored.end()) // Don't go back.
            {
                auto it2 = it->second.find(xx);
                if(it2 != it->second.end())
                {
                    continue;
                }
            }
            int height = gridHeight(xx, yy);
            if(height < curHeight + 2)
            {
                Node* w = new Node();
                w->pos.x = xx;
                w->pos.y = yy;
                explored[yy][xx] = true;
                w->parent = v;
                Q.emplace(w);
            }
        }
    }

    //int steps = setNeighbours(root, 0);
    //std::cout << "steps: " << steps << std::endl;

    char visualGrid[Y][X];
    //memset(visualGrid, '.', X * Y);
    for(int y{0}; y < Y; ++y)
    {
        for(int x{0}; x < X; ++x)
        {
            visualGrid[y][x] = '.';
        }
    }
    int steps = 0;
    if(bestNode != nullptr)
    {
        Node* node = bestNode;
        Node* prev {nullptr};
        //Node* e = new Node();
        //e->pos = end;
        //prev = e;
        //std::cout << "start: " << s.x << ", " << s.y << std::endl;
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

    for(auto p : allNodes)
    {
        delete p;
    }
    allNodes.clear();

    /*for(int y{0}; y < Y; ++y)
    {
        for(int x{0}; x < X; ++x)
        {
            std::cout << static_cast<char>(grid[y][x]);
        }
        std::cout << std::endl;
    }*/


    if(steps == 273)
    {
        std::cout << "start: " << s.x << ", " << s.y << std::endl;
        for(int y{0}; y < Y; ++y)
        {
            for(int x{0}; x < X; ++x)
            {
                std::cout << visualGrid[y][x];
            }
            std::cout << std::endl;
        }
    }
    if(steps > 0)
    {
        std::cout << "actual: " << steps - 1 << std::endl;
        fewestSteps = std::min(steps-1, fewestSteps);
    }
    }

    std::cout << "fewestSteps: " << fewestSteps << std::endl;

    return 0;
}