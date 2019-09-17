#ifndef _ORTHOGRAPHIC_CAMERA_H
#define _ORTHOGRAPHIC_CAMERA_H

#include <glm/glm.hpp>

namespace Bell
{
    class OrthographicCamera
    {
    public:
        OrthographicCamera(float left, float right, float bottom, float top);

        const glm::vec3& GetPosition() const { return m_Position; }
        void SetPosition(const glm::vec3& position) { m_Position = position; RecalculateViewMatrix(); }

        const float GetRotation() const { return m_Rotation; }
        void SetRotation(const float rotation) { m_Rotation = rotation; RecalculateViewMatrix(); }

        const float GetZoom() const { return m_Zoom; }
        void SetZoom(const float zoom) { m_Zoom = zoom; RecalculateViewMatrix(); }

        const glm::mat4 GetProjectionMatrix() const { return m_ProjectionMatrix; }
        const glm::mat4 GetViewMatrix() const { return m_ViewMatrix; }
        const glm::mat4 GetViewProjectionMatrix() const { return m_ViewProjectionMatrix; }
        
    private:
        void RecalculateViewMatrix();

    private:
        glm::mat4 m_ProjectionMatrix;
        glm::mat4 m_ViewMatrix;
        glm::mat4 m_ViewProjectionMatrix;

        glm::vec3 m_Position = { 0.0f, 0.0f, 0.0f };
        float m_Rotation = 0.0f;
        float m_Zoom = 1.0f;
    };
}

#endif // !_ORTHOGRAPHIC_CAMERA_H
