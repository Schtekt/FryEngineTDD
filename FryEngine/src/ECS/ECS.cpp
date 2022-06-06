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

bool ECS::RemoveEntity(Entity ent)
{
    for(auto comp : m_entities[ent])
    {
        size_t typeId = comp.first;
        size_t compId = comp.second;
        m_components[typeId]->RemoveComponent(compId);

                // Find the entity that had the last component of the list.
        size_t lastPosition = m_components[typeId]->GetSize();
        if(m_entities[ent][typeId] != lastPosition)
        {
            for(auto affectedEnt : m_entities)
            {
                if(affectedEnt[typeId] == lastPosition)
                {
                    affectedEnt[typeId] = m_entities[ent][typeId];
                }
            }
        }
    }
    m_entities.erase(m_entities.begin() + ent);
    return true;
}