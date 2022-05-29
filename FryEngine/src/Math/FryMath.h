

struct Vector2
{
    Vector2(float x, float y);
    Vector2& operator=(const Vector2& other);

    // Vector operations
    Vector2 operator+(const Vector2& other) const;
    Vector2 operator-(const Vector2& other) const;
    Vector2 operator/(const Vector2& other) = delete;
    Vector2 operator*(const Vector2& other) = delete;
    Vector2& operator+=(const Vector2& other);
    Vector2& operator-=(const Vector2& other);
    Vector2& operator/=(const Vector2& other) = delete;
    Vector2& operator*=(const Vector2& other) = delete;

    // Scalar operations
    Vector2 operator*(const float& other) const;
    Vector2 operator/(const float& other) const;
    Vector2& operator*=(const float& other);
    Vector2& operator/=(const float& other);

    bool operator==(const Vector2& other) const;
    float Dot(const Vector2& other) const;

    float Length() const;
    Vector2 Normalize() const;

    float x;
    float y;
};

struct Vector3
{
    Vector3(float x, float y, float z);
    Vector3& operator=(const Vector3& other);

    // Vector operations
    Vector3 operator+(const Vector3& other) const;
    Vector3 operator-(const Vector3& other) const;
    Vector3 operator/(const Vector3& other) = delete;
    Vector3 operator*(const Vector3& other) = delete;
    Vector3& operator+=(const Vector3& other);
    Vector3& operator-=(const Vector3& other);
    Vector3& operator/=(const Vector3& other) = delete;
    Vector3& operator*=(const Vector3& other) = delete;

    // Scalar operations
    Vector3 operator*(const float& other) const;
    Vector3 operator/(const float& other) const;
    Vector3& operator*=(const float& other);
    Vector3& operator/=(const float& other);

    bool operator==(const Vector3& other) const;
    float Dot(const Vector3& other) const;
    Vector3 CrossRH(const Vector3 & other) const;
    Vector3 CrossLH(const Vector3 & other) const;

    float Length() const;
    Vector3 Normalize() const;

    float x;
    float y;
    float z;
};

struct Vector4
{
    Vector4(float x, float y, float z, float w);
    Vector4& operator=(const Vector4& other);

    // Vector operations
    Vector4 operator+(const Vector4& other) const;
    Vector4 operator-(const Vector4& other) const;
    Vector4 operator/(const Vector4& other) = delete;
    Vector4 operator*(const Vector4& other) = delete;
    Vector4& operator+=(const Vector4& other);
    Vector4& operator-=(const Vector4& other);
    Vector4& operator/=(const Vector4& other) = delete;
    Vector4& operator*=(const Vector4& other) = delete;

    // Scalar operations
    Vector4 operator*(const float& other) const;
    Vector4 operator/(const float& other) const;
    Vector4& operator*=(const float& other);
    Vector4& operator/=(const float& other);

    bool operator==(const Vector4& other) const;
    float Dot(const Vector4& other) const;

    float Length() const;
    Vector4 Normalize() const;

    float x;
    float y;
    float z;
    float w;
};