#include "ECS.h"
#include <stdexcept>
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

void ECS::UpdateSystem(BaseSystem* system)
{
    if(!system->SystemIsValid())
    {
        throw std::invalid_argument("System without a required component was trying to update!");
    }
    std::vector<void*> comps;
    comps.resize(system->GetComponentTypes().size());

    for(int i = 0; i < comps.size(); i++)
    {
        comps[i] = nullptr;
    }

    // Single component
    if(comps.size() == 1)
    {
        const auto & types = system->GetComponentTypes();

        BaseComponentContainer* compCont = m_components[types[0].first];

        for(int i = 0; i < compCont->GetSize(); i++)
        {
            comps[0] = static_cast<ComponentBase*>(compCont->GetComponentEntry(i))->GetComponent();
            system->UpdateComponents(comps);
        }
    }
    // Multiple components
    else if(comps.size() > 1)
    {
        const auto & types = system->GetComponentTypes();

        BaseComponentContainer* compCont = m_components[types[0].first];

        for(int i = 0; i < compCont->GetSize(); i++)
        {
            ComponentBase* driverComponent = static_cast<ComponentBase*>(compCont->GetComponentEntry(i));
            auto& parent = m_entities[driverComponent->GetEntity()];
            comps[0] = driverComponent->GetComponent();

            TypeId currentType;
            bool foundAllRequired = true;
            for(size_t i = 1; i < types.size(); i++)
            {
                currentType = types[i].first;
                if(parent.count(currentType) != 0)
                {
                    comps[i] = static_cast<ComponentBase*>(m_components[currentType]->GetComponentEntry(parent[currentType]))->GetComponent();
                }
                else if(types[i].second == CompRequired::REQUIRED)
                {
                    foundAllRequired = false;
                    break;
                }
            }

            if(foundAllRequired)
            {
                system->UpdateComponents(comps);
            }

            // reset
            for(int i = 0; i < comps.size(); i++)
            {
                comps[i] = nullptr;
            }
        }
    }
}

void ECS::UpdateSystem(std::initializer_list<BaseSystem*>&& systems)
{
    for(auto system : systems)
    {
        UpdateSystem(system);
    }
}

void ECS::updateSystemMultipleComponents(BaseSystem* system)
{
    const auto & types = system->GetComponentTypes();

    for(int i = 0; i <  m_components[types[0].first]->GetSize(); i++)
    {
    }
}

void ECS::updateSystemSingleComponent(std::initializer_list<BaseSystem*>&& systems)
{
    for(auto system : systems)
    {
        for(auto type : m_components)
        {
            if(type.first == system->GetComponentTypes()[0].first)
            {
                for(int i = 0; i < type.second->GetSize(); i++)
                {
                    std::vector<void*> compVec;
                    compVec.emplace_back(static_cast<ComponentBase*>(type.second->GetComponentEntry(i))->GetComponent());
                    system->UpdateComponents(compVec);
                }
            }
        }
    }
}