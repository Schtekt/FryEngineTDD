#include <gtest/gtest.h>
#include "../../FryEngine/src/FryMath.h"

TEST(FryMathVector, Addition)
{
    Vector3 vec1{1,1,2};
    Vector3 vec2{3,-1,3};
    ASSERT_EQ(vec1 + vec2, Vector3(4,0,5));
}

TEST(FryMathVector, Subtraction)
{
    Vector2 vec1{11,2};
    Vector2 vec2{5,2};
    ASSERT_EQ(vec1 - vec2, Vector2(6,0));
}

TEST(FryMathVector, MultiplyByScalar)
{
    Vector2 vec{20,5};
    ASSERT_EQ(vec * 5, Vector2(100, 25));
}

TEST(FryMathVector, DivideByScalar)
{
    Vector2 vec{20,100};
    ASSERT_EQ(vec / 10, Vector2(2,10));
}

TEST(FryMathVector, LengthOfVector)
{
    Vector4 vec{2,2,2,2};
    ASSERT_EQ(vec.Length(), 4);
}

TEST(FryMathVector, NormalizeVector)
{
    Vector4 vec{1,1,1,1};
    Vector4 tmp = vec.Normalize();
    ASSERT_EQ(tmp, Vector4(1.0f/2,1.0f/2,1.0f/2,1.0f/2));
}

TEST(FryMathVector, DotProduct)
{
    Vector2 vec1{10,1};
    Vector2 vec2{3,2};
    ASSERT_EQ(vec1.Dot(vec2), 32);
}

TEST(FryMathVector, CrossProductRH)
{
    Vector3 vec1{1,0,0};
    Vector3 vec2{0,0,1};

    ASSERT_EQ(vec1.CrossRH(vec2), Vector3(0,-1,0));
}

TEST(FryMathVector, CrossProductLH)
{
    Vector3 vec1{1,0,0};
    Vector3 vec2{0,0,1};

    ASSERT_EQ(vec1.CrossLH(vec2), Vector3(0,1,0));
}