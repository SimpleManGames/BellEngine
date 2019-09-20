#include "bpch.h"
#include "OrthographicCameraController.h"

#include "Bell/Input/Input.h"
#include "Bell/Input/KeyCodes.h"

namespace Bell
{
    OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool rotationEnabled)
        : m_AspectRatio(aspectRatio), m_Camera(-m_AspectRatio * m_ZoomLevel, m_AspectRatio* m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel), m_RotationEnabled(rotationEnabled)
    {
    }

    void OrthographicCameraController::OnUpdate(Timestep deltaTime)
    {
        // Camera
        if (Input::IsKeyPressed(B_KEY_A))
            m_Position.x -= m_TranslationSpeed * deltaTime;
        else if (Input::IsKeyPressed(B_KEY_D))
            m_Position.x += m_TranslationSpeed * deltaTime;

        if (Input::IsKeyPressed(B_KEY_W))
            m_Position.y += m_TranslationSpeed * deltaTime;
        else if (Input::IsKeyPressed(B_KEY_S))
            m_Position.y -= m_TranslationSpeed * deltaTime;

        if (m_RotationEnabled) {
            if (Input::IsKeyPressed(B_KEY_Q))
                m_Rotation += m_RotationSpeed * deltaTime;
            if (Input::IsKeyPressed(B_KEY_E))
                m_Rotation -= m_RotationSpeed * deltaTime;
        }

        // Scale the speed by our far we are zoomed
        m_TranslationSpeed = m_ZoomLevel;

        m_Camera.SetPosition(m_Position);
        m_Camera.SetRotation(m_Rotation);
    }

    void OrthographicCameraController::OnEvent(Event& e)
    {
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<MouseScrolledEvent>(B_BIND_EVENT_FN(OrthographicCameraController::OnMouseScrolled));
        dispatcher.Dispatch<WindowResizeEvent>(B_BIND_EVENT_FN(OrthographicCameraController::OnWindowResize));
    }
    
    bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent& e)
    {
        m_ZoomLevel -= e.GetYOffset() * 0.25f;
        m_ZoomLevel = std::max(m_ZoomLevel, 0.25f);
        m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);

        return false;
    }
    
    bool OrthographicCameraController::OnWindowResize(WindowResizeEvent& e)
    {
        m_AspectRatio = (float)e.GetWidth() / (float)e.GetHeight();
        m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
        return false;
    }
}