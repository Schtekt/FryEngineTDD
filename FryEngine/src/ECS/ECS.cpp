#include "ECS.h"
ECS::ECS()
{

}

ECS::~ECS()
{

}

Entity ECS::CreateEntity()
{
    return m_entities.emplace_back(m_entities.size());
}