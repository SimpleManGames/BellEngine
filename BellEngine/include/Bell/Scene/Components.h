#ifndef _COMPONENTS_H
#define _COMPONENTS_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Bell/Scene/SceneCamera.h"
#include "ScriptableEntity.h"

namespace Bell
{
    /**
     * @brief Component used to set the Name/Tag of an Entity
     * 
     */
    struct TagComponent
    {
        std::string Tag;

        TagComponent() = default;
        TagComponent(const std::string &tag)
            : Tag(tag) {}

        ~TagComponent() = default;
        TagComponent(const TagComponent &) = default;
    };

    /**
     * @brief Component used to describe the Entity's Transform
     * 
     */
    struct TransformComponent
    {
        glm::vec3 Translation = {0.0f, 0.0f, 0.0f};
        glm::vec3 Rotation = {0.0f, 0.0f, 0.0f};
        glm::vec3 Scale = {1.0f, 1.0f, 1.0f};

        TransformComponent() = default;
        TransformComponent(const glm::vec3 &translation)
            : Translation(translation) {}

        ~TransformComponent() = default;
        TransformComponent(const TransformComponent &) = default;

        glm::mat4 GetTransform() const
        {
            glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), Rotation.x, {1, 0, 0}) * glm::rotate(glm::mat4(1.0f), Rotation.y, {0, 1, 0}) * glm::rotate(glm::mat4(1.0f), Rotation.z, {0, 0, 1});

            return glm::translate(glm::mat4(1.0f), Translation) * rotation * glm::scale(glm::mat4(1.0f), Scale);
        }
    };

    /**
     * @brief Component used to render a sprite
     * 
     */
    struct SpriteRendererComponent
    {
        glm::vec4 Color{1.0f, 1.0f, 1.0f, 1.0f};

        SpriteRendererComponent() = default;
        SpriteRendererComponent(const glm::vec4 &color)
            : Color(color) {}

        ~SpriteRendererComponent() = default;
        SpriteRendererComponent(const SpriteRendererComponent &) = default;
    };

    /**
     * @brief Component used to hold information about the camera
     * 
     */
    struct CameraComponent
    {
        SceneCamera Camera;
        /**
         * @brief Used to determine if the Scene should use this camera as Main Camera
         * 
         */
        bool Primary = true;
        /**
         * @brief Sets wether or not this Camera's aspect ratio will adjust with the viewport changes.
         * 
         * @param true Will update when the current viewport is resized.
         * @param false Will ignore viewport resizes and stay at the set ratio.
         * 
         */
        bool FixedAspectRatio = false;

        CameraComponent() = default;
        ~CameraComponent() = default;
        CameraComponent(const CameraComponent &) = default;
    };

    /**
     * @brief Component used to bind Native(C++) scripts for 
     * Instatiation, Destruction and Updating behaviors
     * 
     */
    struct NativeScriptComponent
    {
        ScriptableEntity *Instance = nullptr;

        using InstantiateScript = ScriptableEntity *(*)();
        /**
         * @brief Function Pointer for creating the component class
         * Component must have a Default Constructor
         */
        InstantiateScript InstantiateScriptFunction;

        using DestroyScript = void (*)(NativeScriptComponent *);
        /**
         * @brief Function Pointer for destroying the component class
         * Instance will be set to nullptr
         * 
         */
        DestroyScript DestroyScriptFunction;

        /**
         * @brief Binds the function of class T to this Component
         * 
         * @tparam T Component Type
         */
        template <typename T>
        void Bind()
        {
            // We define what happens during Instantiate and Destroy functions
            InstantiateScriptFunction = []() { return static_cast<ScriptableEntity *>(new T()); };
            DestroyScriptFunction = [](NativeScriptComponent *nsc) { delete nsc->Instance; nsc->Instance = nullptr; };
        }
    };

} // namespace Bell

#endif // _COMPONENTS_H