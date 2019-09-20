#ifndef _ORTHOGRAPHIC_CAMERA_CONTROLLER_H
#define _ORTHOGRAPHIC_CAMERA_CONTROLLER_H

#include "Bell/Renderer/Camera/OrthographicCamera.h"
#include "Bell/Core/Timestep.h"

#include "Bell/Events/ApplicationEvent.h"
#include "Bell/Events/MouseEvent.h"

namespace Bell
{
    class OrthographicCameraController
    {
    public:
        OrthographicCameraController(float aspectRatio, bool rotationEnabled = false); 

        void OnUpdate(Timestep deltaTime);
        void OnEvent(Event& e);

        OrthographicCamera& GetCamera() { return m_Camera; }
        const OrthographicCamera& GetCamera() const { return m_Camera; }

    private:
        bool OnMouseScrolled(MouseScrolledEvent& e);
        bool OnWindowResize(WindowResizeEvent& e);

    private:
        float m_AspectRatio;
        float m_ZoomLevel = 1.0f;

        bool m_RotationEnabled;

    private:
        OrthographicCamera m_Camera;

        glm::vec3 m_Position = { 0.0f, 0.0f, 0.0f };
        float m_Rotation = 0.0f;
        float m_TranslationSpeed = 5.0f, m_RotationSpeed = 180.0f;
    };
}

#endif // !_ORTHOGRAPHIC_CAMERA_CONTROLLER_H
