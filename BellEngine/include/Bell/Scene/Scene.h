#ifndef SCENE_H
#define SCENE_H

#include "entt.hpp"

namespace Bell
{
    class Scene
    {
    public:
        Scene();
        ~Scene();

    private:
        // Registry that stores and manages Entities in this scene
        // Heap alloc'd so clean we be handled automatically
        entt::registry m_Registry;
    };
} // namespace Bell

#endif // SCENE_H