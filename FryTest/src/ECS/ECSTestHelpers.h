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
    DummyDeleteComponent(ObjectStatus& status, const char* text = ""):pStatus(status), name(text) {pStatus = ObjectStatus::Alive;};
    ~DummyDeleteComponent(){pStatus = ObjectStatus::Destroyed;};
    ObjectStatus& pStatus;
    std::string name;
};

struct DummyDeleteComponentSecond
{
    DummyDeleteComponentSecond(ObjectStatus& status):pStatus(status){pStatus = ObjectStatus::Alive;};
    ~DummyDeleteComponentSecond(){pStatus = ObjectStatus::Destroyed;};
    ObjectStatus& pStatus;
};