#include "bpch.h"
#include "Bell/Scene/Entity.h"

namespace Bell
{
    Entity::Entity(entt::entity handle, Scene *scene)
        : m_EntityHandle(handle), m_Scene(scene)
    {
    }
} // namespace Bell