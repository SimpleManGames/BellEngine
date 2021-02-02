#ifndef ENTITY_H
#define ENTITY_H

#include "Scene.h"

#include "entt/entt.hpp"

namespace Bell
{
    /**
     * @brief Wrapper API for EnTT
     * Syntax for adding components is through this class to make it more
     *  human readable instead of through the scene's registry out right.
     * Because of that this Entity will have to know which scene it is
     *  apart of since the backend still treats it as EnTT would expect.
     */
    class Entity
    {
    public:
        /**
         * @brief Default Constructor for Entity objects
         * 
         */
        Entity() = default;

        /**
        * @brief Construct a new Entity object
        * 
        * @param handle EnTT Entity that is created through Scene::CreateEntity
        * @param scene Pointer to the scene that created this Entity
        * So we have access to the registry to alter components for this Entity
        */
        Entity(entt::entity handle, Scene *scene);

        /**
         * @brief Default Copy Construct of an Entity object
         * 
         */
        Entity(const Entity &) = default;

        /**
        * @brief Checks to see if this Entity has this component type
        * @tparam T is the struct of the Component Type you wish to check for
        * @return True if this Entity has this component type, otherwise false
        */
        template <typename T>
        bool HasComponent()
        {
            return m_Scene->m_Registry.has<T>(m_EntityHandle);
        }

        /**
        * @brief Adds a component to this Entity
        * 
        * @warning 
        * Trying to add a component to an Entity that already 
        * has component type of T will result in an assertion
        * 
        * @tparam T Component Type you wish to add.
        * @tparam Args Types of arguments to initilize the component with.
        * @param args Parameters to use to initialize the component.
        * @return Reference to the new component.
        */
        template <typename T, typename... Args>
        T &AddComponent(Args &&...args)
        {
            B_CORE_ASSERT(!HasComponent<T>(), "Entity you are trying to add a component to already has that Component Type");
            return m_Scene->m_Registry.emplace<T>(m_EntityHandle, std::forward<Args>(args)...);
        }

        /**
        * @brief Adds a component to this Entity
        * 
        * @warning
        * Trying to get a component type from this Entity that doesn't have
        * the type already added will result in an assertion
        * 
        * @param args Parameters to use to initialize the component.
        * @return Reference to the new component
        */
        template <typename T>
        T &GetComponent()
        {
            B_CORE_ASSERT(HasComponent<T>(), "Entity you are trying to get a component from does NOT have Component Type");
            return m_Scene->m_Registry.get<T>(m_EntityHandle);
        }

        /**
         * @brief Removes a component from an Entity
         * 
         * @tparam T Component Type
         */
        template <typename T>
        void RemoveComponent()
        {
            m_Scene->m_Registry.remove<T>(m_EntityHandle);
        }

        operator bool() const { return m_EntityHandle != entt::null; }

    private:
        entt::entity m_EntityHandle = entt::null;
        // Temp solution until we handle our own ref counting
        Scene *m_Scene = nullptr;
    };

} // namespace Bell

#endif // ENTITY_H