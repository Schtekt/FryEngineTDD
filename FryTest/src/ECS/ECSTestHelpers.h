#include <string>

class DummyComponent
{
 public:
    DummyComponent(std::string name, float num): m_name(name), m_num(num) {};

    std::string m_name;
    float m_num;
};

enum ObjectStatus
{
    Alive = 0,
    Destroyed = 1
};

struct DummyDeleteComponent
{
    DummyDeleteComponent(std::shared_ptr<ObjectStatus>& status, const char* text = ""):spStatus(status), name(text) {*spStatus.get() = ObjectStatus::Alive;};
    ~DummyDeleteComponent(){if(spStatus.use_count() == 2){*spStatus.get() = ObjectStatus::Destroyed;}};
    std::shared_ptr<ObjectStatus> spStatus;
    std::string name;
};

struct DummyDeleteComponentSecond
{
    DummyDeleteComponentSecond(std::shared_ptr<ObjectStatus>& status):spStatus(status){*spStatus.get() = ObjectStatus::Alive;};
    ~DummyDeleteComponentSecond(){*spStatus.get() = ObjectStatus::Destroyed;};
    std::shared_ptr<ObjectStatus> spStatus;
};