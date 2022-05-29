#include <vector>
using Entity = size_t;

class ECS
{
 public:
    ECS();
    ~ECS();

    Entity CreateEntity();
private:
    std::vector<Entity> m_entities;
};