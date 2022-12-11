#pragma once

//#include <boost/multiprecision/gmp.hpp>

class Item
{
public:
    Item(uint64_t worryLevel) : _worryLevel{worryLevel}
    {

    }

    uint64_t worryLevel() const
    {
        return _worryLevel;
    }

    void setWorryLevel(uint64_t worryLevel)
    {
        _worryLevel = worryLevel;
    }

private:
    uint64_t _worryLevel;
};