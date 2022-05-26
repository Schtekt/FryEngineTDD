#include "FryMath.h"
#include "math.h"

Vector2 Vector2::operator+(const Vector2& other) const
{
    return Vector2({x + other.x, y + other.y});
}

Vector2 Vector2::operator-(const Vector2& other) const
{
    return Vector2({x - other.x, y - other.y});
}

Vector2 Vector2::operator+=(const Vector2& other)
{
    x += other.x;
    y += other.y;
    return *this;
}

Vector2 Vector2::operator-=(const Vector2& other)
{
    x -= other.x;
    y -= other.y;
    return *this;
}

bool Vector2::operator==(const Vector2& other) const
{
    return x == other.x && y == other.y;
}

float Vector2::Dot(const Vector2& other) const
{
    return x * other.x + y * other.y;
}

float Vector2::Length() const
{
    return sqrtf(x * x + y*y);
}

Vector2 Vector2::Normal() const
{
    return *this;
}