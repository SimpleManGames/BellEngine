#ifndef _CAMERA_H
#define _CAMERA_H

#include <glm/glm.hpp>

namespace Bell
{
    class Camera
    {
    public:
        Camera(glm::mat4 projectionMatrix, glm::mat4 viewMatrix);

        const glm::mat4 GetProjectionMatrix() const { return m_ProjectionMatrix; }
        const glm::mat4 GetViewMatrix() const { return m_ViewMatrix; }
        const glm::mat4 GetViewProjectionMatrix() const { return m_ViewProjectionMatrix; }

    protected:
        glm::mat4 m_ProjectionMatrix;
        glm::mat4 m_ViewMatrix;
        glm::mat4 m_ViewProjectionMatrix;
    };
}

#endif // !_CAMERA_H
