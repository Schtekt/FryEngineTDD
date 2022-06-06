class DummyComponent;
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

    ASSERT_NE(ent1, ent2);
}

class DummyComponent
{
 public:
    DummyComponent(std::string name, float num): m_name(name), m_num(num) {};

    std::string m_name;
    float m_num;
};

TEST(ECSComponent, CreateCompponent)
{
    ECS ecs;

    Entity ent = ecs.CreateEntity();

    ecs.CreateComponent<DummyComponent>(ent, "MyDummy", 5.5f);

    DummyComponent* comp = ecs.GetComponent<DummyComponent>(ent);

    ASSERT_TRUE(comp);
    ASSERT_EQ(comp->m_name, "MyDummy");
    ASSERT_EQ(comp->m_num, 5.5f);
}

TEST(ECSComponent, CreateMultipleOfSameComponent)
{
    ECS ecs;
    
    Entity ent1 = ecs.CreateEntity();
    Entity ent2 = ecs.CreateEntity();

    ecs.CreateComponent<DummyComponent>(ent1, "MyDummy", 5.5f);
    ecs.CreateComponent<DummyComponent>(ent2, "MySecondDummy", 10.5f);

    DummyComponent* comp1 = ecs.GetComponent<DummyComponent>(ent1);
    DummyComponent* comp2 = ecs.GetComponent<DummyComponent>(ent2);

    ASSERT_TRUE(comp1 && comp2);
    ASSERT_EQ(comp1->m_name, "MyDummy");
    ASSERT_EQ(comp1->m_num, 5.5f);
    ASSERT_EQ(comp2->m_name, "MySecondDummy");
    ASSERT_EQ(comp2->m_num, 10.5f);

}

TEST(ECSComponent, CreateMultipleOfMultipleComponents)
{
    ECS ecs;
    
    Entity ent1 = ecs.CreateEntity();
    Entity ent2 = ecs.CreateEntity();

    ecs.CreateComponent<DummyComponent>(ent1, "MyDummy", 5.5f);
    ecs.CreateComponent<float>(ent2, 15.0f);
    ecs.CreateComponent<DummyComponent>(ent2, "MySecondDummy", 10.5f);
    ecs.CreateComponent<std::string>(ent1, "This is a string...");

    DummyComponent* comp1   = ecs.GetComponent<DummyComponent>(ent1);
    float* comp2            = ecs.GetComponent<float>(ent2);
    DummyComponent* comp3   = ecs.GetComponent<DummyComponent>(ent2);
    std::string* comp4      = ecs.GetComponent<std::string>(ent1);

    ASSERT_TRUE(comp1 && comp2 && comp3 && comp4);
    ASSERT_EQ(comp1->m_name, "MyDummy");
    ASSERT_EQ(comp1->m_num, 5.5f);
    ASSERT_EQ(*comp2, 15.0f);
    ASSERT_EQ(comp3->m_name, "MySecondDummy");
    ASSERT_EQ(comp3->m_num, 10.5f);
    ASSERT_EQ(*comp4 ,"This is a string...");
}

enum ObjectStatus
{
    Alive = 0,
    Destroyed = 1
};

struct DummyDeleteComponent
{
    DummyDeleteComponent(ObjectStatus& status):pStatus(status){pStatus = ObjectStatus::Alive;};
    ~DummyDeleteComponent(){pStatus = ObjectStatus::Destroyed;};
    ObjectStatus& pStatus;
};

TEST(ECSComponent, RemoveComponent)
{
    ECS ecs;
    Entity ent1 = ecs.CreateEntity();
    Entity ent2 = ecs.CreateEntity();

    ObjectStatus status1;
    ObjectStatus status2;
    ecs.CreateComponent<DummyDeleteComponent>(ent1, status1);
    ecs.CreateComponent<DummyDeleteComponent>(ent2, status2);
    
    EXPECT_EQ(status1, ObjectStatus::Alive);
    EXPECT_EQ(status2, ObjectStatus::Alive);

    ecs.RemoveComponent<DummyDeleteComponent>(ent1);
    EXPECT_EQ(status1, ObjectStatus::Destroyed);
    EXPECT_EQ(status2, ObjectStatus::Alive);

    EXPECT_FALSE(ecs.GetComponent<DummyDeleteComponent>(ent1));
}

struct DummyDeleteComponentSecond
{
    DummyDeleteComponentSecond(ObjectStatus& status):pStatus(status){pStatus = ObjectStatus::Alive;};
    ~DummyDeleteComponentSecond(){pStatus = ObjectStatus::Destroyed;};
    ObjectStatus& pStatus;
};

TEST(ECSEntity, RemoveEntity)
{
    ECS ecs;
    Entity ent1 = ecs.CreateEntity();
    Entity ent2 = ecs.CreateEntity();

    ObjectStatus status1;
    ObjectStatus status2;
    ObjectStatus status3;
    ecs.CreateComponent<DummyDeleteComponent>(ent1, status1);
    ecs.CreateComponent<DummyDeleteComponentSecond>(ent1, status2);
    ecs.CreateComponent<DummyDeleteComponent>(ent2, status3);
    
    EXPECT_EQ(status1, ObjectStatus::Alive);
    EXPECT_EQ(status2, ObjectStatus::Alive);
    EXPECT_EQ(status3, ObjectStatus::Alive);

    ecs.RemoveEntity(ent1);
    EXPECT_EQ(status1, ObjectStatus::Destroyed);
    EXPECT_EQ(status2, ObjectStatus::Destroyed);
    EXPECT_EQ(status3, ObjectStatus::Alive);
}