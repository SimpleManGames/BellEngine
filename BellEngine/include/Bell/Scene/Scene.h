#ifndef SCENE_H
#define SCENE_H

#include "Bell/Base/Time.h"
#include "entt/entt.hpp"

#include <glm/glm.hpp>

namespace Bell
{
    class Entity;
    namespace Editor
    {
        class SceneHierarchyPanel;
    }

    class Scene
    {
    public:
        Scene();
        ~Scene();

        /**
         * @brief Handles all scene related code such as submitting to the render,
         * updating entities and their interactions
         * 
         * @param ts Delta Time
         */
        void OnUpdate(Timestep ts);

        /**
         * @brief Processes if the viewport has changed and will update entities accordingly
         * 
         * @param width New Viewport width
         * @param height New Viewport height
         */
        void OnViewportResize(uint32_t width, uint32_t height);

        /**
         * @brief Create a Entity object
         * Also will add a TransformComponent by default
         * 
         * @param tag Set the tag component's value during Entity creation - 
         * Defaults to an empty string.
         * @param translation Set the translation of the Entity during creation - 
         * Defaults to an Identity Matrix
         * 
         * @return Newly created Entity
         */
        Entity CreateEntity(const std::string &tag = "Entity", const glm::vec3 &translation = glm::vec3(0.0f));

    private:
        // Registry that stores and manages Entities in this scene
        // Heap alloc'd so clean we be handled automatically
        entt::registry m_Registry;

        uint32_t m_ViewportWidth = 0, m_ViewportHeight = 0;

        friend class Entity;
        friend class Editor::SceneHierarchyPanel;
    };
} // namespace Bell

#endif // SCENE_H