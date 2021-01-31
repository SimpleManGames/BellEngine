#include "bpch.h"
#include "Bell/Renderer/Camera/Camera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Bell
{
    Camera::Camera(const glm::mat4& projectionMatrix)
        : m_ProjectionMatrix(projectionMatrix)
    {
    }
}