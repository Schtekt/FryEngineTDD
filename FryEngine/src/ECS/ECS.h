#pragma once
#include <memory>
#include <vector>
#include <map>
#include "Component.h"
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
private:
    std::vector<std::map<TypeId, ComponentId>> m_entities;

    std::vector<BaseComponentType*> m_compTypes;
    std::map<size_t, std::vector<char>> m_components;
};

template<typename T, typename ...Args>
bool ECS::CreateComponent(Entity ent, Args&& ... args)
{
    size_t typeId = ComponentType<T>::GetId();
    if(m_entities[ent].count(typeId) == 0)
    {
        std::vector<T>* currTypeList = reinterpret_cast<std::vector<T>*>(&m_components[typeId]);

        m_entities[ent][typeId] = currTypeList->size();

        size_t sizeOfComponent = ComponentType<T>::GetSize();
        size_t oldSizeOfVector = m_components[typeId].size();

        m_components[typeId].resize(oldSizeOfVector + sizeOfComponent);

        new (&m_components[typeId].at(oldSizeOfVector)) T(std::forward<Args>(args)...);
        return true;
    }
    return false;
}

template<typename T>
T* ECS::GetComponent(Entity ent)
{
    size_t typeId = ComponentType<T>::GetId();
    if(m_entities[ent].count(typeId) > 0)
    {
        std::vector<T>* currTypeList = reinterpret_cast<std::vector<T>*>(&m_components[typeId]);
        return &currTypeList->at(m_entities[ent][typeId]);
    }
    return nullptr;
}

template<typename T>
bool ECS::RemoveComponent(Entity ent)
{
    size_t typeId = ComponentType<T>::GetId();
    if(m_entities[ent].count(typeId) > 0)
    {
        std::vector<T>* currTypeList = reinterpret_cast<std::vector<T>*>(&m_components[typeId]);
        ComponentType<T>::CallDestructor(&currTypeList->at(m_entities[ent][typeId]));

        // Component removed, to avoid moving all components and to keep component creation consistent, 
        // swap its with the last component and reduce the size of the vector by one component.
        std::memcpy(
            &currTypeList->at(m_entities[ent][typeId]), 
            &currTypeList->at(currTypeList->size() - 1), 
            ComponentType<T>::GetSize()
        );

        m_components[typeId].resize(m_components[typeId].size() - ComponentType<T>::GetSize());

        return true;
    }
    return false;
}