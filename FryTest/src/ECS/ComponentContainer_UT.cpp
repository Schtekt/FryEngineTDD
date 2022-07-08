#include <gtest/gtest.h>
#include "ECS/ComponentContainer.h"
#include "ECSTestHelpers.h"

TEST(ECSComponentContainer, Instantiate)
{
    std::unique_ptr<BaseComponentContainer> ptr(new ComponentContainer<DummyDeleteComponent>);
}

TEST(ECSComponentContainer, GetComponent)
{
    ObjectStatus stat;
    {
        ComponentContainer<DummyDeleteComponent> compCont;

        stat = ObjectStatus::Alive;
        DummyDeleteComponent* compPtr = (DummyDeleteComponent*)compCont.GetComponentEntry(compCont.Emplace(stat, "Hello"));
        ASSERT_TRUE(compPtr);
        ASSERT_EQ(stat, ObjectStatus::Alive);
        ASSERT_EQ(compPtr->name, "Hello");
    }
    ASSERT_EQ(stat, ObjectStatus::Destroyed);
}