#pragma once
#include <vector>
#include "ComponentContainer.h"
using TypeId = size_t;

class BaseSystem
{
public:
    virtual void UpdateComponent(void* comp) = 0;
    TypeId GetComponentType() const {return m_ComponentType;}

protected:
    template<typename T>
    void addComponentType();

private:
    TypeId m_ComponentType;
};

template<typename T>
void BaseSystem::addComponentType()
{
    m_ComponentType = ComponentContainer<T>::GetId();
}