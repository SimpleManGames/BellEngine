#ifndef _COMPONENTS_H
#define _COMPONENTS_H

#include <glm/glm.hpp>

#include "Bell/Scene/SceneCamera.h"

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

} // namespace Bell

#endif // _COMPONENTS_H