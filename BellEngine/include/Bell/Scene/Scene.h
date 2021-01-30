#ifndef SCENE_H
#define SCENE_H

#include "Bell/Base/Time.h"
#include "entt/entt.hpp"

#include <glm/glm.hpp>

namespace Bell
{
    class Entity;

    class Scene
    {
    public:
        Scene();
        ~Scene();

        void OnUpdate(Timestep ts);

        /**
         * @brief Create a Entity object
         * Also will add a TransformComponent by default
         * 
         * @param tag Set the tag component's value during Entity creation - 
         * Defaults to an empty string.
         * @param transform Set the transform of the Entity during creation - 
         * Defaults to an Identity Matrix
         * 
         * @return Newly created Entity
         */
        Entity CreateEntity(const std::string &tag = "Entity", const glm::mat4 &transform = glm::mat4(1.0f));

    private:
        // Registry that stores and manages Entities in this scene
        // Heap alloc'd so clean we be handled automatically
        entt::registry m_Registry;

        friend class Entity;
    };
} // namespace Bell

#endif // SCENE_H