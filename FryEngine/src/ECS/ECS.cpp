#include "ECS.h"
ECS::ECS()
{

}

ECS::~ECS()
{

}

Entity ECS::CreateEntity()
{
    m_entities.emplace_back();
    return m_entities.size() - 1;
}