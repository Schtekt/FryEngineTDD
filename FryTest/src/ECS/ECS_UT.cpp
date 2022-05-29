#include <gtest/gtest.h>
#include "ECS/ECS.h"

TEST(ECSEntity, CreateEntity)
{
    ECS ecs;
    Entity ent = ecs.CreateEntity();
    ASSERT_TRUE(ent == 0);
}

TEST(ECSEntity, CreateMultipleEntities)
{
    ECS ecs;
    Entity ent1 = ecs.CreateEntity();
    Entity ent2 = ecs.CreateEntity();

    ASSERT_TRUE(ent1 != ent2);
}