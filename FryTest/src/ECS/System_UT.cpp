#include <gtest/gtest.h>
#include "ECS/ECS.h"

class AddOneSystem : public BaseSystem
{
    public:
    AddOneSystem()
    {
        addComponentType<int>();
    }

    void UpdateComponents(std::vector<void*> components){
        int* num = static_cast<int*>(components[0]);
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

    void UpdateComponents(std::vector<void*> components){
        int* num = static_cast<int*>(components[0]);
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

    void UpdateComponents(std::vector<void*> components){
        int* num = static_cast<int*>(components[0]);
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

    ecs.CreateComponent<int>(ent1, 5);
    ecs.CreateComponent<double>(ent1, 3.3);
    ecs.CreateComponent<int>(ent2, 10);

    AddOneSystem addOne;
    MultiplySystem multiplyFive(5);
    ecs.UpdateSystem({&addOne, &multiplyFive});

    EXPECT_EQ(*ecs.GetComponent<int>(ent1), 6 * 5);
    EXPECT_EQ(*ecs.GetComponent<double>(ent1), 3.3);
    EXPECT_EQ(*ecs.GetComponent<int>(ent2), 11 * 5);
}

struct position
{
    float x, y, z;
    position(float x, float y, float z){this->x = x; this->y = y; this->z = z;}
    bool operator==(const position & other) const 
    {return x == other.x && y == other.y && z == other.z; };
};

struct velocity
{
    float x, y, z;
    velocity(float x, float y, float z){this->x = x; this->y = y; this->z = z;}
    bool operator==(const velocity & other) const {return x == other.x && y == other.y && z == other.z; };
};

struct acceleration
{
    float x, y, z;
    acceleration(float x, float y, float z){this->x = x; this->y = y; this->z = z;}
    bool operator==(const acceleration & other) const {return x == other.x && y == other.y && z == other.z; };
};

class PositionSystem : public BaseSystem
{
public:
    PositionSystem()
    {
        addComponentType<position>(CompRequired::REQUIRED);
        addComponentType<velocity>(CompRequired::OPTIONAL);
        addComponentType<acceleration>(CompRequired::OPTIONAL);
    }

    virtual void UpdateComponents(std::vector<void*> comps)
    {
        position* pos = reinterpret_cast<position*>(comps[0]);
        velocity* vel = reinterpret_cast<velocity*>(comps[1]);
        acceleration* acc = reinterpret_cast<acceleration*>(comps[2]);

        if(acc && vel)
        {
            pos->x += (acc->x * m_dt * m_dt / 2) + vel->x * m_dt;
            pos->y += (acc->y * m_dt * m_dt / 2) + vel->y * m_dt;
            pos->z += (acc->z * m_dt * m_dt / 2) + vel->z * m_dt;

            vel->x += acc->x * m_dt;
            vel->y += acc->y * m_dt;
            vel->z += acc->z * m_dt;
        }
        else if(acc)
        {
            pos->x += (acc->x * m_dt * m_dt / 2);
            pos->y += (acc->y * m_dt * m_dt / 2);
            pos->z += (acc->z * m_dt * m_dt / 2);
        }
        else if(vel)
        {
            pos->x += vel->x * m_dt;
            pos->y += vel->y * m_dt;
            pos->z += vel->z * m_dt;
        }
    }

    void SetDt(float dt) {m_dt = dt;}
private:
    float m_dt = 0.0f;
};

TEST(ECSSystem, UpdateMultipleComponentsInOneSystem)
{
    ECS ecs;

    Entity ent1 = ecs.CreateEntity();
    Entity ent2 = ecs.CreateEntity();
    Entity ent3 = ecs.CreateEntity();

    ecs.CreateComponent<position>(ent1, 0.0f,0.0f,0.0f);
    ecs.CreateComponent<velocity>(ent1, 1.0f,0.0f,0.0f);

    ecs.CreateComponent<position>(ent2, 0.0f,0.0f,0.0f);
    ecs.CreateComponent<velocity>(ent2, 0.0f,-1.0f,0.0f);
    ecs.CreateComponent<acceleration>(ent2, 0.0f,1.0f,0.0f);

    ecs.CreateComponent<position>(ent3, 0.0f,0.0f,5.0f);

    PositionSystem sys;
    sys.SetDt(2.0f);

    ecs.UpdateSystem(&sys);

    position resPosFirst{2.0f, 0.0f, 0.0f};
    position posFirst = *ecs.GetComponent<position>(ent1);
    
    position resPosSecond{0.0f, 0.0f, 0.0f};
    position posSecond = *ecs.GetComponent<position>(ent2);
    velocity resVelSecond{0.0f, 1.0f, 0.0f};
    velocity velSecond = *ecs.GetComponent<velocity>(ent2);

    position resPosThird{0.0f, 0.0f, 5.0f};
    position posThird = *ecs.GetComponent<position>(ent3);

    ASSERT_EQ(posFirst, resPosFirst);

    ASSERT_EQ(posSecond, resPosSecond);
    ASSERT_EQ(velSecond, resVelSecond);

    ASSERT_EQ(posThird, resPosThird);
}

class InvalidSystem : public BaseSystem
{
    public:
    InvalidSystem()
    {
        addComponentType<position>(CompRequired::OPTIONAL);
        addComponentType<velocity>(CompRequired::OPTIONAL);
        addComponentType<acceleration>(CompRequired::OPTIONAL);
    }

    void UpdateComponents(std::vector<void*> component)
    {
    }
};

TEST(ECSSystem, UpdateWithNoDriver)
{
    ECS ecs;

    Entity ent = ecs.CreateEntity();

    ecs.CreateComponent<position>(ent, 0.0f,0.0f,0.0f);
    ecs.CreateComponent<velocity>(ent, 0.0f,0.0f,0.0f);
    ecs.CreateComponent<acceleration>(ent, 0.0f,0.0f,0.0f);

    InvalidSystem sys;

    try
    {
        ecs.UpdateSystem(&sys);
        FAIL() << "Expected std::invalid_argument";
    }
    catch(const std::invalid_argument & e)
    {
        EXPECT_EQ(e.what(), std::string("System without a required component was trying to update!"));
    }
    catch(...)
    {
        FAIL() << "Expected std::invalid_argument";
    }
    
}