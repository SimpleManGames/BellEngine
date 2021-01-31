#ifndef _CAMERA_H
#define _CAMERA_H

#include <glm/glm.hpp>

namespace Bell
{
    class Camera
    {
    public:
        Camera(glm::mat4 &projectionMatrix);

        const glm::mat4 GetProjectionMatrix() const { return m_ProjectionMatrix; }

    protected:
        glm::mat4 m_ProjectionMatrix;
    };
} // namespace Bell

#endif // !_CAMERA_H
