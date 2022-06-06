#include <gtest/gtest.h>
#include "ECS/ComponentContainer.h"

enum ObjectStatus
{
    Alive = 0,
    Destroyed = 1
};

struct DummyDeleteComponent
{
    DummyDeleteComponent(ObjectStatus& status, const char* text):pStatus(status), name(text) {pStatus = ObjectStatus::Alive;};
    ~DummyDeleteComponent(){pStatus = ObjectStatus::Destroyed;};
    ObjectStatus& pStatus;
    std::string name;
};

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
        DummyDeleteComponent* compPtr = (DummyDeleteComponent*)compCont.GetComponent(compCont.Emplace(stat, "Hello"));
        ASSERT_TRUE(compPtr);
        ASSERT_EQ(stat, ObjectStatus::Alive);
        ASSERT_EQ(compPtr->name, "Hello");
    }
    ASSERT_EQ(stat, ObjectStatus::Destroyed);
}