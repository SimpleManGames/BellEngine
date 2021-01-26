#include "bpch.h"
#include "Bell/Renderer/Camera/OrthographicCameraController.h"

#include "Bell/Base/Input/Input.h"
#include "Bell/Base/Input/KeyCodes.h"

namespace Bell
{
    OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool rotationEnabled)
        : m_AspectRatio(aspectRatio), m_Bounds({-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel}),
          m_Camera(m_Bounds.Left, m_Bounds.Right, m_Bounds.Bottom, m_Bounds.Top),
          m_RotationEnabled(rotationEnabled)
    {
        B_PROFILE_FUNCTION();
        Input::Remap("camera_move_left", KeyAlternative(Keys::A));
        Input::Remap("camera_move_right", KeyAlternative(Keys::D));
        Input::Remap("camera_move_up", KeyAlternative(Keys::W));
        Input::Remap("camera_move_down", KeyAlternative(Keys::S));

        Input::Remap("camera_rotate_clockwise", KeyAlternative(Keys::E));
        Input::Remap("camera_rotate_counter_clockwise", KeyAlternative(Keys::Q));
    }

    void OrthographicCameraController::OnUpdate(Timestep deltaTime)
    {
        B_PROFILE_FUNCTION();
        glm::vec3 position = GetPosition();
        float rotation = GetRotation();

        // Camera
        if (Input::IsInputPressed("camera_move_left"))
            position.x -= m_TranslationSpeed * deltaTime;
        else if (Input::IsInputPressed("camera_move_right"))
            position.x += m_TranslationSpeed * deltaTime;

        if (Input::IsInputPressed("camera_move_up"))
            position.y += m_TranslationSpeed * deltaTime;
        else if (Input::IsInputPressed("camera_move_down"))
            position.y -= m_TranslationSpeed * deltaTime;

        if (m_RotationEnabled)
        {
            if (Input::IsInputPressed("camera_rotate_counter_clockwise"))
                rotation += m_RotationSpeed * deltaTime;
            if (Input::IsInputPressed("camera_rotate_clockwise"))
                rotation -= m_RotationSpeed * deltaTime;
        }

        // Scale the speed by our far we are zoomed
        m_TranslationSpeed = m_ZoomLevel;

        m_Camera.SetPosition(position);
        m_Camera.SetRotation(rotation);
    }

    void OrthographicCameraController::OnEvent(Event &e)
    {
        B_PROFILE_FUNCTION();
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<MouseScrolledEvent>(B_BIND_EVENT_FN(OrthographicCameraController::OnMouseScrolled));
        dispatcher.Dispatch<WindowResizeEvent>(B_BIND_EVENT_FN(OrthographicCameraController::OnWindowResize));
    }

    void OrthographicCameraController::CalculateView()
    {
        m_Bounds = {-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel};
        m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
    }

    bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent &e)
    {
        B_PROFILE_FUNCTION();
        m_ZoomLevel -= e.GetYOffset() * 0.25f;
        m_ZoomLevel = std::max(m_ZoomLevel, 0.25f);
        CalculateView();

        return false;
    }

    bool OrthographicCameraController::OnWindowResize(WindowResizeEvent &e)
    {
        B_PROFILE_FUNCTION();
        OnResize((float)e.GetWidth(), (float)e.GetHeight());
        return false;
    }

    void OrthographicCameraController::OnResize(float width, float height)
    {
        m_AspectRatio = width / height;
        CalculateView();
    }
} // namespace Bell