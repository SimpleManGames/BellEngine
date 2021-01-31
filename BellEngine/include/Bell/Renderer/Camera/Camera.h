#ifndef _CAMERA_H
#define _CAMERA_H

#include <glm/glm.hpp>

namespace Bell
{
    class Camera
    {
    public:
        Camera() = default;
        Camera(const glm::mat4 &projectionMatrix);

        /**
         * @brief Get the Projection Matrix
         * 
         * @return const glm::mat4 Current Project Matrix
         */
        const glm::mat4 GetProjectionMatrix() const { return m_ProjectionMatrix; }

    protected:
        glm::mat4 m_ProjectionMatrix = glm::mat4(1.0f);
    };
} // namespace Bell

#endif // !_CAMERA_H
