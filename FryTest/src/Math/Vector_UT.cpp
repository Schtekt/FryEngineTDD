#include <gtest/gtest.h>
#include "../../FryEngine/src/FryMath.h"

TEST(FryMathVector, Addition)
{
    Vector2 vec1{1,1};
    Vector2 vec2{3,-1};
    ASSERT_EQ(vec1 + vec2, Vector2({4,0}));
}