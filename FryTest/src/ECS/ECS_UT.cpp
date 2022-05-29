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

    ASSERT_TRUE(ent1 != ent2);
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
    ASSERT_TRUE(comp->m_name == "MyDummy" && comp->m_num == 5.5f);
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
    ASSERT_TRUE(comp1->m_name == "MyDummy" && comp1->m_num == 5.5f && 
                comp2->m_name == "MySecondDummy" && comp2->m_num == 10.5f);

}

TEST(ECSComponent, CreateMultippleOfMultipleComponents)
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
    ASSERT_TRUE(comp1->m_name == "MyDummy" && comp1->m_num == 5.5f && 
                *comp2 == 15.0f &&
                comp3->m_name == "MySecondDummy" && comp3->m_num == 10.5f &&
                *comp4 == "This is a string...");
}