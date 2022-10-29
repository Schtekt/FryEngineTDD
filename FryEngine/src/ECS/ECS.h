#pragma once
#include <memory>
#include <vector>
#include <map>
#include "System.h"
using Entity = size_t;
using TypeId = size_t;
using ComponentId = size_t;

class ECS
{
 public:
    ECS();
    ~ECS() = default;

    Entity CreateEntity();
    template<typename T, typename ...Args>
    bool CreateComponent(Entity ent, Args &&... args);
    template<typename T>
    T* GetComponent(Entity ent);
    template<typename T>
    bool RemoveComponent(Entity ent);
    bool RemoveEntity(Entity ent);
    void UpdateSystem(BaseSystem* system);
    void UpdateSystem(std::initializer_list<BaseSystem*>&& systems);
private:
    void updateSystemMultipleComponents(BaseSystem* system);
    void updateSystemSingleComponent(std::initializer_list<BaseSystem*>&& systems);
    bool removeComponentInternal(TypeId type, ComponentId id);
    std::vector<std::map<TypeId, ComponentId>> m_entities;
    std::map<TypeId, std::unique_ptr<BaseComponentContainer>> m_components;
};

template<typename T, typename ...Args>
bool ECS::CreateComponent(Entity ent, Args&& ... args)
{
    size_t typeId = ComponentContainer<ComponentEntry<T>>::GetId();
    if(m_components.count(typeId) == 0)
    {
        m_components[typeId] = std::make_unique<ComponentContainer<ComponentEntry<T>>>();
    }

    if(m_entities[ent].count(typeId) == 0)
    {
        auto* requestedContainer = reinterpret_cast<ComponentContainer<ComponentEntry<T>>*>(m_components[typeId].get());

        m_entities[ent][typeId] = requestedContainer->Emplace(ent, std::forward<Args>(args)...);
        return true;
    }
    return false;
}

template<typename T>
T* ECS::GetComponent(Entity ent)
{
    size_t typeId = ComponentContainer<ComponentEntry<T>>::GetId();
    if(m_entities[ent].count(typeId) > 0)
    {
        auto* componentEntry = static_cast<ComponentEntry<T>*>(m_components[typeId]->GetComponentEntry(m_entities[ent][typeId]));
        return static_cast<T*>(componentEntry->GetComponent());
    }
    return nullptr;
}

template<typename T>
bool ECS::RemoveComponent(Entity ent)
{
    size_t typeId = ComponentContainer<ComponentEntry<T>>::GetId();
    if(m_entities[ent].count(typeId) > 0)
    {
        m_components[typeId]->RemoveComponent(m_entities[ent][typeId]);

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
        m_entities[ent].erase(typeId);

        return true;
    }
    return false;
}