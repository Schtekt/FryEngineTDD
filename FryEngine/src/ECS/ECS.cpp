#include "ECS.h"
ECS::ECS()
{

}

ECS::~ECS()
{
    for(auto compCont : m_components)
    {
        delete compCont.second;
    }
}

Entity ECS::CreateEntity()
{
    m_entities.emplace_back();
    return m_entities.size() - 1;
}