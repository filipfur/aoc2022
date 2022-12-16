#include <iostream>
#include <map>
#include <vector>
#include "../lib/vec2.h"
#include <cmath>
#include <functional>

static const long long startY{2000000};
//static const long long startY{10};

class Sensor
{
public:
    Sensor(Vec2 position, Vec2 beacon) : _position{position}, _beacon{beacon}
    {
        Vec2 d = beacon - position;
        _radii2 = d.x * d.x + d.y * d.y;
    }

    Vec2 position() const
    {
        return _position;
    }

    Vec2 beacon() const
    {
        return _beacon;
    }

    long long radii2() const
    {
        return _radii2;
    }

    bool shouldCull(long long y)
    {
        if(_position.y > y)
        {
            if((_position.y - sqrt(_radii2)) <= y)
            {
                return false;
            }
        }
        if(_position.y < y)
        {
            if((_position.y + sqrt(_radii2)) >= y)
            {
                return false;
            }
        }
        else
        {
            return false;
        }
        return true;
    }

    void doPrint()
    {
        std::cout << "Sensor x=" << _position.x << ", y=" << _position.y << " Beacon x=" << _beacon.x << ", y=" << _beacon.y << std::endl;
    }

private:
    Vec2 _position;
    Vec2 _beacon;
    long long maxRange;
    long long _radii2;
};

class Grid
{
public:
    Grid() : _map{}
    {

    }

    // Deprecated
    void placeSensor(const Sensor& sensor)
    {
        //Vec2 delta = sensor.position() - sensor.beacon();
        setTile(sensor.position().x, sensor.position().y, 'S');
        setTile(sensor.beacon().x, sensor.beacon().y, 'B');
    }
// 6164953 <- gissat
    long long doMath(std::vector<Sensor>& sensors, long long y)
    {
        std::cout << "min: " << _min[0] << ", " << _min[1] << std::endl;
        std::cout << "max: " << _max[0] << ", " << _max[1] << std::endl;

        int count{0};
        for(long long x{_min[0] - 100000000L}; x < _max[0] + 100000000L; ++x)
        {
            if(false && x % 1000 == 0)
            {
                std::cout << "doing work: " << x << ", max=" << _max[0] << std::endl;
            }
            Vec2 p{x, y};
            auto it = sensors.begin();
            while(it != sensors.end())
            {
                Vec2 d = it->position() - p;
                long long len = (d.x * d.x + d.y * d.y);
                long long radii2 = it->radii2();
                if(abs(d.x) < radii2 && len <= radii2)
                {
                    //std::cout << "delta: " << d.x << ", " << d.y << std::endl;
                    //std::cout << "len: " << len << std::endl;
                    //std::cout << "raddiiii2: " << it->radii2() << std::endl;
                    if(getTile(p.x, p.y) == 0)
                    {
                        setTile(p.x, p.y, '#', false);
                        ++count;
                    }
                    break;
                    ++it;
                }
                else if(d.x < 0)
                {
                    it = sensors.erase(it);
                }
                else
                {
                    ++it;
                }
            }
        }
        return count;
    }

    void setTile(long long x, long long y, char c, bool updateminmax=true)
    {
        if(updateminmax)
        {
            _min[0] = std::min(x, _min[0]);
            _min[1] = std::min(y, _min[1]);
            _max[0] = std::max(x, _max[0]);
            _max[1] = std::max(y, _max[1]);
        }
        _map[y][x] = c;
    }

    char getTile(long long x, long long y)
    {
        auto it = _map.find(y);
        if(it != _map.end())
        {
            auto it2 = it->second.find(x);
            if(it2 != it->second.end())
            {
                return it2->second;
            }
        }
        return 0;
    }

    void doPrint()
    {
        for(long long y{_min[1] - 1}; y  < _max[1] + 1; ++y)
        {
            for(long long x{_min[0] - 1}; x  < _max[0] + 1; ++x)
            {
                char tile = getTile(x, y);
                std::cout << (tile ? tile : '.');
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }

private:
    long long _min[2];
    long long _max[2];
    std::map<long long, std::map<long long, char>> _map;
};

int main(int argc, const char* argv[])
{
    Grid grid{};
    std::vector<Sensor> sensors{};
    std::string str;
    while(getline(std::cin, str))
    {
        int data[4];
        size_t a = str.find_first_of('=');
        int i{0};
        while(a != std::string::npos)
        {
            a += 1;
            size_t b0 = str.find_first_of(',', a);
            size_t b;
            if(b0 == std::string::npos)
            {
                //data[i++] = std::stoi(str.substr(a));
                b = str.size();
            }
            else
            {
                size_t b1 = str.find_first_of(':', a);
                b = std::min(b0, b1);
                //data[i++] = std::stoi(str.substr(a, b - a));
            }
            data[i++] = std::stoi(str.substr(a, b - a));
            str = str.substr(b);
            a = str.find_first_of('=');
        }

        sensors.push_back(Sensor{Vec2{data[0], data[1]}, Vec2{data[2], data[3]}});
    }
    auto it = sensors.begin();

    int cullCount{0};
    while(it != sensors.end())
    {
        it->doPrint();
        grid.placeSensor(*it);
        if(it->shouldCull(startY))
        {
            it = sensors.erase(it);
            ++cullCount;
        }
        else
        {
            grid.placeSensor(*it);
            ++it;
        }
    }

    std::cout << "culling: " << cullCount << std::endl;
    
    //grid.doPrint();

    //grid.doMath(sensors, 9);
    //int res = grid.doMath(sensors, 10);
    //grid.doMath(sensors, 11);

    long long res = grid.doMath(sensors, startY);

    //grid.doPrint();

    std::cout << "result: " << res << std::endl;

    return 0;
}