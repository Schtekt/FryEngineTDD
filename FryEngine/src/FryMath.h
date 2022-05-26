

class Vector2
{
 public:
    Vector2 operator+(const Vector2& other) const;
    Vector2 operator-(const Vector2& other) const;
    Vector2 operator/(const Vector2& other) = delete;
    Vector2 operator*(const Vector2& other) = delete;
    Vector2 operator+=(const Vector2& other);
    Vector2 operator-=(const Vector2& other);
    Vector2 operator/=(const Vector2& other) = delete;
    Vector2 operator*=(const Vector2& other) = delete;
    bool operator==(const Vector2& other) const;
    float Dot(const Vector2& other) const;

    float Length() const;
    Vector2 Normal() const;

    float x;
    float y;
};

class Vector3
{
 public:
    // Operators
    Vector3 operator+(const Vector3& other) const;
    Vector3 operator-(const Vector3& other) const;
    Vector3 operator/(const Vector3& other) = delete;
    Vector3 operator*(const Vector3& other) = delete;
    Vector3 operator+=(const Vector3& other);
    Vector3 operator-=(const Vector3& other);
    Vector3 operator/=(const Vector3& other) = delete;
    Vector3 operator*=(const Vector3& other) = delete;
    bool operator==(const Vector3& other) const;
    float Dot(const Vector3& other) const;
    Vector3 Cross(const Vector3& other) const;

    float Length() const;
    Vector3 Normal() const;

    float x;
    float y;
    float z;
};