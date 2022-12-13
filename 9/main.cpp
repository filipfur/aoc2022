#include <iostream>
#include <vector>
#include "../lib/vec2.h"

static constexpr int N{1024};

class Stalker
{
public:

    Stalker(char id, Vec2 start, Vec2* subject, char (&grid)[N][N] ) : _id{id}, _self{start}, _subject{subject}, _grid{grid}
    {

    }

    void follow()
    {
        Vec2 delta = *_subject - _self;
        int distance2 = delta.x * delta.x + delta.y * delta.y;
        if(distance2 > 2)
        {
            if(delta.x != 0) { delta.x /= abs(delta.x); }
            if(delta.y != 0) { delta.y /= abs(delta.y); }
            _self += delta;
            if(_id == '9')
            {
                _grid[_self.y][_self.x] = _id;//toChar(_seq++); 
            }
            //std::cout << "tail.x=" << _self.x << ", tail.y=" << _self.y << ", d.x=" << delta.x << ", d.y" << delta.y << std::endl;
        }
    }

    Vec2* selfPtr()
    {
        return &_self;
    }

    Vec2 self()
    {
        return _self;
    }

    char id()
    {
        return _id;
    }

private:
    char _id;
    Vec2 _self;
    Vec2* _subject;
    char (&_grid)[N][N];
};

class World
{
public:
    World() : _grid{}, _gridhead{}
    {
        //_grid[_head.y][_head.x] = 's';
        //std::memset(_grid, '.', N*N);
        //std::memset(_gridhead, '.', N*N);

        for(int i{0}; i < 9; ++i)
        {
            Stalker* stalker = new Stalker('1' + i, _start, i == 0 ? &_head : _stalkers[i - 1]->selfPtr(), _grid);
            _stalkers[i] = stalker;
        }

        for(int y{0}; y < N; ++y)
        {
            for(int x{0}; x < N; ++x)
            {
                _grid[y][x] = '.';
                _gridhead[y][x] = '.';
            }
        }
    }

    void execute(char command, int argument)
    {
        switch(command)
        {
            case 'U':
                _delta = Vec2{0, -1};
                break;
            case 'L':
                _delta = Vec2{-1, 0};
                break;
            case 'D':
                _delta = Vec2{0, 1};
                break;
            case 'R':
                _delta = Vec2{1, 0};
                break;
        }
        std::cout << "executing command=" << command << ", argument=" << argument << std::endl;
        _distance = argument;
    }

    bool work()
    {
        if(_distance > 0)
        {
            _head += _delta;
            _distance -= 1;
            _gridhead[_head.y][_head.x] = toChar(_seqhead++);
            //std::cout << "head.x=" << _head.x << ", head.y=" << _head.y << ", d.x=" << _delta.x << ", d.y" << _delta.y << std::endl;
            //_stalker.follow();
            for(auto stalker : _stalkers)
            {
                stalker->follow();
            }
            return true;
        }
        return false;
    }

    bool onTile(const Vec2& pos, int x, int y)
    {
        return pos.x == x && pos.y == y;
    }

    char toChar(int seq)
    {
        return '#';
        if(seq < 10)
        {
            return '0' + seq;
        }
        return 'A' + seq - 10;
    }

    void print()
    {
        for(int y{0}; y < N; ++y)
        {
            for(int x{0}; x < N; ++x)
            {
                char c = '.';
                if(onTile(_head, x, y))
                {
                    c = 'H';
                }
                /*else if(onTile(_start, x, y))
                {
                    c = 's';
                }*/
                else
                {
                    for(int i{0}; i < 9; ++i)
                    {
                        if(onTile(_stalkers[i]->self(), x, y))
                        {
                            c = _stalkers[i]->id();
                            break;
                        }
                    }
                }


                std::cout << c;//_grid[y][x];
            }
            std::cout << std::endl;
        }
    }

    int result()
    {
        int visits{0};
        for(int y{0}; y < N; ++y)
        {
            for(int x{0}; x < N; ++x)
            {
                char c = _grid[y][x];
                if(onTile(_start, x, y))
                {
                    c = '@';
                }
                if(c != '.')
                {
                    ++visits;
                }
                //std::cout << ' ' << c;
            }
            //std::cout << std::endl;
        }
        return visits;
    }

    void resulthead()
    {
        for(int y{0}; y < N; ++y)
        {
            for(int x{0}; x < N; ++x)
            {
                char c = _gridhead[y][x];
                if(onTile(_start, x, y))
                {
                    c = '@';
                }
                std::cout << ' ' << c;
            }
            std::cout << std::endl;
        }
    }

    char _grid[N][N];
    char _gridhead[N][N];
    Stalker* _stalkers[9];
    Vec2 _delta{0,0};
    Vec2 _start{N/2, N/2};
    Vec2 _head{_start};
    //Stalker _stalker;
    int _seq{0};
    int _seqhead{0};
    int _distance{};
};

int main(int argc, const char* argv[])
{
    World world{};
    char c;
    while(std::cin >> c)
    {
        int i;
        std::cin >> i;
        world.execute(c, i);
        while(world.work())
        {
        }
        //world.print();
    }
    std::cout << std::endl;
    int res = world.result();
    //world.resulthead();
    std::cout << "tail visited: " << res << std::endl;
    return 0;
}