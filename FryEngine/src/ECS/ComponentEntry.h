using Entity = size_t;

struct ComponentBase
{
    virtual Entity GetEntity() = 0;
    virtual void* GetComponent() = 0;
    virtual ~ComponentBase() {};
};

template<typename T>
struct ComponentEntry: public ComponentBase
{
    template<typename ...Args>
    ComponentEntry(Entity ent, Args && ... args) : m_Entity(ent), m_Component(std::forward<Args>(args)...) {}
    ~ComponentEntry() {}
    Entity GetEntity() {return m_Entity;}
    void* GetComponent() {return &m_Component;}

    Entity m_Entity;
    T m_Component;
};