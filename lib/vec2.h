#pragma once

struct Vec2
{
    long long x{0};
    long long y{0};

    Vec2() : Vec2{0, 0}
    {

    }

    Vec2(const Vec2& other) : Vec2{other.x, other.y}
    {

    }

    Vec2(long long x, long long y) : x{x}, y{y}
    {

    }

    Vec2& operator+=(const Vec2& other)
    {
        x += other.x;
        y += other.y;
        return *this;
    }

    Vec2& operator=(const Vec2& other)
    {
        x = other.x;
        y = other.y;
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