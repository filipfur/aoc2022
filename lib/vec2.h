#pragma once

struct Vec2
{
    int x{0};
    int y{0};

    Vec2() : Vec2{0, 0}
    {

    }

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