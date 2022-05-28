#include "FryMath.h"
#include "math.h"

// Vector2

Vector2::Vector2(float x, float y)
{
    this->x = x;
    this->y = y;
}

Vector2 Vector2::operator+(const Vector2& other) const
{
    return Vector2({x + other.x, y + other.y});
}

Vector2 Vector2::operator-(const Vector2& other) const
{
    return Vector2({x - other.x, y - other.y});
}

Vector2& Vector2::operator+=(const Vector2& other)
{
    x += other.x;
    y += other.y;
    return *this;
}

Vector2& Vector2::operator-=(const Vector2& other)
{
    x -= other.x;
    y -= other.y;
    return *this;
}

Vector2 Vector2::operator*(const float& other) const
{
    return Vector2(x * other, y * other);
}

Vector2 Vector2::operator/(const float& other) const
{
    return Vector2(x / other, y / other);
}
Vector2& Vector2::operator*=(const float& other)
{
    x *= other;
    y *= other;
    return *this;
}
Vector2& Vector2::operator/=(const float& other)
{
    x /= other;
    y /= other;
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

Vector2 Vector2::Normalize() const
{
    return *this / Length();
}

// Vector 3

Vector3::Vector3(float x, float y, float z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}
Vector3& Vector3::operator=(const Vector3& other)
{
    x = other.x;
    y = other.y;
    z = other.z;
    return *this;
}

// Vector operations
Vector3 Vector3::operator+(const Vector3& other) const
{
    return Vector3(x + other.x, y + other.y, z + other.z);
}

Vector3 Vector3::operator-(const Vector3& other) const
{
    return Vector3(x - other.x, y - other.y, z - other.z);
}

Vector3& Vector3::operator+=(const Vector3& other)
{
    x += other.x;
    y += other.y;
    z += other.z;
    return *this;
}

Vector3& Vector3::operator-=(const Vector3& other)
{
    x -= other.x;
    y -= other.y;
    z -= other.z;
    return *this;
}

// Scalar operations
Vector3 Vector3::operator*(const float& other) const
{
    return Vector3(x * other, y * other, z * other);
}

Vector3 Vector3::operator/(const float& other) const
{
    return Vector3(x / other, y / other, z / other);
}

Vector3& Vector3::operator*=(const float& other)
{
    x *= other;
    y *= other;
    z *= other;
    return *this;
}

Vector3& Vector3::operator/=(const float& other)
{
    x /= other;
    y /= other;
    z /= other;
    return *this;
}

bool Vector3::operator==(const Vector3& other) const
{
    return x == other.x && y == other.y && z == other.z;
}

float Vector3::Dot(const Vector3& other) const
{
    return x * other.x + y * other.y + z * other.z;
}

Vector3 Vector3::CrossRH(const Vector3 & other) const
{
    return Vector3(y * other.z - z * other.y , z * other.x - x * other.z, x * other.y - y * other.x);
}

Vector3 Vector3::CrossLH(const Vector3 & other) const
{
    return Vector3(z * other.y - y * other.z, x * other.z - z * other.x, y * other.x - x * other.y);
}

float Vector3::Length() const
{
    return sqrtf(Dot(*this));
}

Vector3 Vector3::Normalize() const
{
    return *this / Length();
}

// Vector 4

Vector4::Vector4(float x, float y, float z, float w)
{
    this->x = x;
    this->y = y;
    this->z = z;
    this->w = w;
}

Vector4& Vector4::operator=(const Vector4& other)
{
    x = other.x;
    y = other.y;
    z = other.z;
    w = other.w;
    return *this;
}

// Vector operations
Vector4 Vector4::operator+(const Vector4& other) const
{
    return Vector4(x + other.x, y + other.y, z + other.z, w + other.w);
}

Vector4 Vector4::operator-(const Vector4& other) const
{
    return Vector4(x - other.x, y - other.y, z - other.z, w - other.w);
}

Vector4& Vector4::operator+=(const Vector4& other)
{
    x += other.x;
    y += other.y;
    z += other.z;
    w += other.w;
    return *this;
}

Vector4& Vector4::operator-=(const Vector4& other)
{
    x -= other.x;
    y -= other.y;
    z -= other.z;
    w -= other.w;
    return *this;
}

// Scalar operations
Vector4 Vector4::operator*(const float& other) const
{
    return Vector4(x * other, y * other, z * other, w * other);
}

Vector4 Vector4::operator/(const float& other) const
{
    return Vector4(x / other, y / other, z / other, w / other);
}

Vector4& Vector4::operator*=(const float& other)
{
    x *= other;
    y *= other;
    z *= other;
    w *= other;
    return *this;
}

Vector4& Vector4::operator/=(const float& other)
{
    x /= other;
    y /= other;
    z /= other;
    w /= other;
    return *this;
}

bool Vector4::operator==(const Vector4& other) const
{
    return x == other.x && y == other.y && z == other.z && w == other.w;
}

float Vector4::Dot(const Vector4& other) const
{
    return x * other.x + y * other.y + z * other.z + w * other.w;
}

float Vector4::Length() const
{
    return sqrtf(Dot(*this));
}

Vector4 Vector4::Normalize() const
{
    return *this / Length();
}