#include <gtest/gtest.h>
#include "ECS/ComponentContainer.h"
#include "ECSTestHelpers.h"

TEST(ECSComponentContainer, Instantiate)
{
    std::unique_ptr<BaseComponentContainer> ptr(std::make_unique<ComponentContainer<DummyDeleteComponent>>());
}

TEST(ECSComponentContainer, GetComponent)
{
    auto stat = std::make_shared<ObjectStatus>();
    {
        ComponentContainer<DummyDeleteComponent> compCont;

        DummyDeleteComponent* compPtr = (DummyDeleteComponent*)compCont.GetComponentEntry(compCont.Emplace(stat, "Hello"));
        ASSERT_TRUE(compPtr);
        ASSERT_EQ(*stat.get(), ObjectStatus::Alive);
        ASSERT_EQ(compPtr->name, "Hello");
    }
    ASSERT_EQ(*stat.get(), ObjectStatus::Destroyed);
}