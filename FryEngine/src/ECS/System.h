#pragma once
#include <vector>
#include "ComponentContainer.h"
#include "ComponentEntry.h"
using TypeId = size_t;
enum class CompRequired
{
    REQUIRED,
    OPTIONAL
};

class BaseSystem
{
public:
    BaseSystem(){}
    virtual void UpdateComponents(std::vector<void*> comps) = 0;
    std::vector<std::pair<TypeId, CompRequired>> const & GetComponentTypes() const {return m_ComponentTypes;}
    bool SystemIsValid() {return m_RequiredSet;}

protected:
    template<typename T>
    void addComponentType(CompRequired requirementStatus = CompRequired::REQUIRED);
private:
    bool m_RequiredSet = false;
    std::vector<std::pair<TypeId, CompRequired>> m_ComponentTypes;
};

template<typename T>
void BaseSystem::addComponentType(CompRequired requirementStatus)
{
    if(!m_RequiredSet && requirementStatus == CompRequired::REQUIRED)
    {
         m_ComponentTypes.insert(m_ComponentTypes.begin(), {ComponentContainer<ComponentEntry<T>>::GetId(), requirementStatus});
         m_RequiredSet = true;
    }
    else
    {
        m_ComponentTypes.emplace_back(ComponentContainer<ComponentEntry<T>>::GetId(), requirementStatus);
    }
}