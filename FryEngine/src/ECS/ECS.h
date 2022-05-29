#pragma once
#include <memory>
#include <vector>
#include <map>
#include "Component.h"
using Entity = size_t;

class ECS
{
 public:
    ECS();
    ~ECS();

    Entity CreateEntity();
    template<typename T, typename ...Args>
    void CreateComponent(Entity ent, Args... args);
    template<typename T>
    T* GetComponent(Entity ent);
private:
    std::vector<Entity> m_entities;

    std::vector<BaseComponentType*> m_compTypes;
    std::map<size_t, std::vector<char>> m_components;
    std::map<size_t, std::vector<Entity>> m_compToEntityRel;
};

template<typename T, typename ...Args>
void ECS::CreateComponent(Entity ent, Args... args)
{
    size_t typeId = ComponentType<T>::GetId();
    std::vector<T>* currTypeList = reinterpret_cast<std::vector<T>*>(&m_components[typeId]);
    currTypeList->emplace_back(std::forward<Args>(args)...);

    m_compToEntityRel[typeId].emplace_back(ent);
}

template<typename T>
T* ECS::GetComponent(Entity ent)
{
    size_t typeId = ComponentType<T>::GetId();
    for(int i = 0; i < m_compToEntityRel[typeId].size(); i++)
    {
        if(m_compToEntityRel[typeId].at(i) == ent)
        {
            return (T*)(&m_components[typeId].at(ComponentType<T>::GetSize() * i));
        }
    }
    return nullptr;
}