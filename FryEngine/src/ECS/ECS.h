#pragma once
#include <memory>
#include <vector>
#include <map>
#include "ComponentContainer.h"
using Entity = size_t;
using TypeId = size_t;
using ComponentId = size_t;

class ECS
{
 public:
    ECS();
    ~ECS();

    Entity CreateEntity();
    template<typename T, typename ...Args>
    bool CreateComponent(Entity ent, Args &&... args);
    template<typename T>
    T* GetComponent(Entity ent);
    template<typename T>
    bool RemoveComponent(Entity ent);
    bool RemoveEntity(Entity ent);
private:
    bool removeComponentInternal(TypeId type, ComponentId id);
    std::vector<std::map<TypeId, ComponentId>> m_entities;
    std::map<TypeId, BaseComponentContainer*> m_components;
};

template<typename T, typename ...Args>
bool ECS::CreateComponent(Entity ent, Args&& ... args)
{
    size_t typeId = ComponentContainer<T>::GetId();
    if(m_components.count(typeId) == 0)
    {
        m_components[typeId] = new ComponentContainer<T>();
    }

    if(m_entities[ent].count(typeId) == 0)
    {
        m_entities[ent][typeId] = reinterpret_cast<ComponentContainer<T>*>(m_components[typeId])->Emplace(std::forward<Args>(args)...);
        return true;
    }
    return false;
}

template<typename T>
T* ECS::GetComponent(Entity ent)
{
    size_t typeId = ComponentContainer<T>::GetId();
    if(m_entities[ent].count(typeId) > 0)
    {
        return reinterpret_cast<T*>(m_components[typeId]->GetComponent(m_entities[ent][typeId]));
    }
    return nullptr;
}

template<typename T>
bool ECS::RemoveComponent(Entity ent)
{
    size_t typeId = ComponentContainer<T>::GetId();
    if(m_entities[ent].count(typeId) > 0)
    {
        m_components[typeId]->RemoveComponent(m_entities[ent][typeId]);

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
        // The entity no longer has that component. Remove it.
        m_entities[ent].erase(typeId);

        return true;
    }
    return false;
}