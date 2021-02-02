#ifndef _COMPONENTS_H
#define _COMPONENTS_H

#include <glm/glm.hpp>

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
        glm::mat4 Transform{1.0f};

        TransformComponent() = default;
        TransformComponent(const glm::mat4 &transform)
            : Transform(transform) {}

        ~TransformComponent() = default;
        TransformComponent(const TransformComponent &) = default;

        float &X() { return Transform[3][0]; }
        float &Y() { return Transform[3][1]; }
        float &Z() { return Transform[3][2]; }

        // Operator for easier usage and cleaner code
        operator glm::mat4 &() { return Transform; }
        operator const glm::mat4 &() const { return Transform; }
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

        using DestroyScript = void(*)(NativeScriptComponent*);
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
            InstantiateScriptFunction = []() { return static_cast<ScriptableEntity*>(new T()); };
            DestroyScriptFunction = [](NativeScriptComponent* nsc) { delete nsc->Instance; nsc->Instance = nullptr; };
        }
    };

} // namespace Bell

#endif // _COMPONENTS_H