#ifndef _ORTHOGRAPHIC_CAMERA_H
#define _ORTHOGRAPHIC_CAMERA_H

#include "Bell/Renderer/Camera/Camera.h"
#include <glm/glm.hpp>

namespace Bell
{
    class OrthographicCamera : public Camera
    {
    public:
        OrthographicCamera(float left, float right, float bottom, float top);

        void SetProjection(float left, float right, float bottom, float top);

        const glm::vec3 &GetPosition() const { return m_Position; }
        void SetPosition(const glm::vec3 &position)
        {
            m_Position = position;
            RecalculateViewMatrix();
        }

        float &GetRotation() { return m_Rotation; }
        const float GetRotation() const { return m_Rotation; }
        void SetRotation(const float rotation)
        {
            m_Rotation = rotation;
            RecalculateViewMatrix();
        }

        const glm::mat4 GetViewMatrix() const { return m_ViewMatrix; }
        const glm::mat4 GetViewProjectionMatrix() const { return m_ViewProjectionMatrix; }

    private:
        void RecalculateViewMatrix();

    private:
        glm::vec3 m_Position = {0.0f, 0.0f, 0.0f};
        float m_Rotation = 0.0f;

        glm::mat4 m_ViewMatrix;
        glm::mat4 m_ViewProjectionMatrix;
    };
} // namespace Bell

#endif // !_ORTHOGRAPHIC_CAMERA_H
