#ifndef _COMPONENTS_H
#define _COMPONENTS_H

#include <glm/glm.hpp>

#include "Bell/Renderer/Camera/Camera.h"

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
        Bell::Camera Camera;
        bool Primary = true;

        CameraComponent() = default;
        CameraComponent(glm::mat4 &projection)
            : Camera(projection) {}

        ~CameraComponent() = default;
        CameraComponent(const CameraComponent &) = default;
    };

} // namespace Bell

#endif // _COMPONENTS_H