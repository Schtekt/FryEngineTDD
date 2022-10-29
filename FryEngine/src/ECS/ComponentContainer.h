#pragma once
#include "vector"

class BaseComponentContainer
{
 protected:
    static size_t assignId();
    static size_t m_sIdCount;
    std::vector<char> m_compList;
 public:
    virtual size_t GetSize() const = 0;
    virtual void* GetComponentEntry(size_t index) = 0;
    virtual void RemoveComponent(size_t index) = 0;
    virtual ~BaseComponentContainer() = default;
};


template<typename T>
class ComponentContainer : public BaseComponentContainer
{
 public:
    virtual ~ComponentContainer();
    static size_t GetId();
    static size_t GetSizeOfComp();
    size_t GetSize() const;

    template<typename ... Args>
    size_t Emplace(Args && ... args);
    void* GetComponentEntry(size_t index);
    void RemoveComponent(size_t index);

 private:
    static size_t m_sId;
    static size_t m_sSizeOfComp;
};

template<typename T>
ComponentContainer<T>::~ComponentContainer()
{
    std::vector<T>* reinterpretCompList = reinterpret_cast<std::vector<T>*>(&m_compList);

    for(auto it = reinterpretCompList->begin(); it != reinterpretCompList->end(); it++)
    {
        (*it).~T();
    }
}

template<typename T>
size_t ComponentContainer<T>::m_sId(BaseComponentContainer::assignId());

template<typename T>
size_t ComponentContainer<T>::m_sSizeOfComp(sizeof(T));

template<typename T>
size_t ComponentContainer<T>::GetId()
{
    return m_sId;
}

template<typename T>
size_t ComponentContainer<T>::GetSizeOfComp()
{
    return m_sSizeOfComp;
}

template<typename T>
size_t ComponentContainer<T>::GetSize() const
{
    return m_compList.size() / m_sSizeOfComp;
}

template<typename T>
template<typename ... Args>
size_t ComponentContainer<T>::Emplace(Args && ... args)
{
    size_t currSize = m_compList.size();
    m_compList.resize(currSize + m_sSizeOfComp);
    new (&m_compList[currSize]) T(std::forward<Args>(args)...);
    return (m_compList.size() / m_sSizeOfComp) - 1;
}

template<typename T>
void* ComponentContainer<T>::GetComponentEntry(size_t index)
{
    std::vector<T>* reinterpretCompList = reinterpret_cast<std::vector<T>*>(&m_compList);
    return &reinterpretCompList->at(index);
}

template<typename T>
void ComponentContainer<T>::RemoveComponent(size_t index)
{
    size_t actualPos = index * m_sSizeOfComp;
    reinterpret_cast<T*>(&m_compList[index])->~T();

    memcpy(
        &m_compList[actualPos],
        &m_compList[m_compList.size() - m_sSizeOfComp],
        m_sSizeOfComp);

    m_compList.resize(m_compList.size() - m_sSizeOfComp);
}