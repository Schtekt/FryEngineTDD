#include <gtest/gtest.h>
#include "ECS/ECS.h"

class AddOneSystem : public BaseSystem
{
    public:
    AddOneSystem()
    {
        addComponentType<int>();
    }

    void UpdateComponent(void* component){
        int* num = static_cast<int*>(component);
        (*num)++;
    }
};

TEST(ECSSystem, UpdateSingleComponentWithSingleSystem)
{
    ECS ecs;

    Entity ent1 = ecs.CreateEntity();
    Entity ent2 = ecs.CreateEntity();
    Entity ent3 = ecs.CreateEntity();

    ecs.CreateComponent<int>(ent1, 5);
    ecs.CreateComponent<double>(ent2, 3.3);
    ecs.CreateComponent<int>(ent3, 10);

    AddOneSystem addOne;
    ecs.UpdateSystem(&addOne);

    EXPECT_EQ(*ecs.GetComponent<int>(ent1), 6);
    EXPECT_EQ(*ecs.GetComponent<double>(ent2), 3.3);
    EXPECT_EQ(*ecs.GetComponent<int>(ent3), 11);
}

class MultiplySystem : public BaseSystem
{
    public:
    MultiplySystem(int multiplier): m_multiplier(multiplier)
    {
        addComponentType<int>();
    }

    void UpdateComponent(void* component){
        int* num = static_cast<int*>(component);
        (*num) *= m_multiplier;
    }

    private:
    int m_multiplier;
};

TEST(ECSSystem, UpdateSingleComponentWithMultipleSystems)
{
    ECS ecs;

    Entity ent1 = ecs.CreateEntity();
    Entity ent2 = ecs.CreateEntity();
    Entity ent3 = ecs.CreateEntity();

    ecs.CreateComponent<int>(ent1, 5);
    ecs.CreateComponent<double>(ent2, 3.3);
    ecs.CreateComponent<int>(ent3, 10);

    AddOneSystem addOne;
    MultiplySystem multiplyFive(5);
    ecs.UpdateSystem({&addOne, &multiplyFive});

    EXPECT_EQ(*ecs.GetComponent<int>(ent1), 6 * 5);
    EXPECT_EQ(*ecs.GetComponent<double>(ent2), 3.3);
    EXPECT_EQ(*ecs.GetComponent<int>(ent3), 11 * 5);
}

class DivideSystem : public BaseSystem
{
 public:
    DivideSystem(int divider): m_divider(divider)
    {
        addComponentType<int>();
    }

    void UpdateComponent(void* component){
        int* num = static_cast<int*>(component);
        (*num) *= m_divider;
    }

 private:
    int m_divider;
};

TEST(ECSSystem, UpdateMultipleComponentsWithMultipleSystems)
{
    ECS ecs;

    Entity ent1 = ecs.CreateEntity();
    Entity ent2 = ecs.CreateEntity();
    Entity ent3 = ecs.CreateEntity();

    ecs.CreateComponent<int>(ent1, 5);
    ecs.CreateComponent<double>(ent2, 3.3);
    ecs.CreateComponent<int>(ent3, 10);

    AddOneSystem addOne;
    MultiplySystem multiplyFive(5);
    ecs.UpdateSystem({&addOne, &multiplyFive});

    EXPECT_EQ(*ecs.GetComponent<int>(ent1), 6 * 5);
    EXPECT_EQ(*ecs.GetComponent<double>(ent2), 3.3);
    EXPECT_EQ(*ecs.GetComponent<int>(ent3), 11 * 5);
}