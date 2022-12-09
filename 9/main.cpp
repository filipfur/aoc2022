#include <iostream>
#include <vector>

struct Vec2
{
    int x{0};
    int y{0};

    Vec2(const Vec2& other) : Vec2{other.x, other.y}
    {

    }

    Vec2(int x, int y) : x{x}, y{y}
    {

    }

    Vec2& operator+=(const Vec2& other)
    {
        x += other.x;
        y += other.y;
        return *this;
    }

    Vec2& operator-=(const Vec2& other)
    {
        x -= other.x;
        y -= other.y;
        return *this;
    }

    Vec2 operator+(const Vec2& other) const
    {
        return Vec2{x + other.x, y + other.y};
    }

    Vec2 operator-(const Vec2& other) const
    {
        return Vec2{x - other.x, y - other.y};
    }
};

class World
{
public:
    World() : _grid{}, _gridhead{}
    {
        //_grid[_head.y][_head.x] = 's';
        //std::memset(_grid, '.', N*N);
        //std::memset(_gridhead, '.', N*N);
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
            std::cout << "head.x=" << _head.x << ", head.y=" << _head.y << ", d.x=" << _delta.x << ", d.y" << _delta.y << std::endl;
            return true;
        }
        return false;
    }

    void follow()
    {
        Vec2 delta = _head - _tail;
        int distance2 = delta.x * delta.x + delta.y * delta.y;
        if(distance2 > 2)
        {
            delta.x /= abs(delta.x);
            delta.y /= abs(delta.y);
            _tail = _tail + delta;
            _grid[_tail.y][_tail.x] = toChar(_seq++); 
            std::cout << "tail.x=" << _tail.x << ", tail.y=" << _tail.y << ", d.x=" << delta.x << ", d.y" << delta.y << std::endl;
        }
    }

    bool onTile(const Vec2& pos, int x, int y)
    {
        return pos.x == x and pos.y == y;
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
                else if(onTile(_start, x, y))
                {
                    c = 's';
                }
                else if(onTile(_tail, x, y))
                {
                    c = 'T';
                    _grid[y][x] = '#';
                }


                std::cout << ' ' << c;//_grid[y][x];
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
                std::cout << ' ' << c;
            }
            std::cout << std::endl;
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

    static constexpr int N{16};
    char _grid[N][N];
    char _gridhead[N][N];
    Vec2 _delta{0,0};
    Vec2 _start{N/2, N/2};
    Vec2 _head{_start};
    Vec2 _tail{_start};
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
            world.follow();
            //world.print();
        }
    }
    std::cout << std::endl;
    int res = world.result();
    world.resulthead();
    std::cout << "tail visited: " << res << std::endl;
    return 0;
}