#pragma once
class BaseComponentType
{
 protected:
    static size_t assignId();
    static size_t m_sIdCount;
 public:
    virtual size_t GetId() = 0;
    virtual size_t GetSize() = 0;
    virtual void CallDestructor(void* ptr) = 0;
};


template<typename T>
class ComponentType : public BaseComponentType
{
 public:
    static size_t GetId();
    static size_t GetSize();
    static void CallDestructor(void* ptr);
 private:
    static size_t m_sId;
    static size_t m_sSizeOfComp;
};

template<typename T>
size_t ComponentType<T>::GetId()
{
    return m_sId;
}

template<typename T>
size_t ComponentType<T>::GetSize()
{
    return m_sSizeOfComp;
}

template<typename T>
void ComponentType<T>::CallDestructor(void* ptr)
{
    static_cast<T*>(ptr)->~T();
}

template<typename T>
size_t ComponentType<T>::m_sId(BaseComponentType::assignId());

template<typename T>
size_t ComponentType<T>::m_sSizeOfComp(sizeof(T));