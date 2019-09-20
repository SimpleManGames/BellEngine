#include "bpch.h"
#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Bell
{
    Camera::Camera(glm::mat4 projectionMatrix, glm::mat4 viewMatrix)
        : m_ProjectionMatrix(projectionMatrix), m_ViewMatrix(viewMatrix)
    {
    }
}