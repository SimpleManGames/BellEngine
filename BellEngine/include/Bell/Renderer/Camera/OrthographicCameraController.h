#ifndef _ORTHOGRAPHIC_CAMERA_CONTROLLER_H
#define _ORTHOGRAPHIC_CAMERA_CONTROLLER_H

#include "Bell/Renderer/Camera/OrthographicCamera.h"
#include "Bell/Base/Time.h"

#include "Bell/Base/Events/ApplicationEvent.h"
#include "Bell/Base/Events/MouseEvent.h"

namespace Bell
{
    struct OrthographicCameraBounds
    {
        float Left, Right;
        float Bottom, Top;

        float GetWidth() { return Right - Left; }
        float GetHeight() { return Top - Bottom; }
    };

    class OrthographicCameraController
    {
    public:
        OrthographicCameraController(float aspectRatio, bool rotationEnabled = false);

        void OnUpdate(Timestep deltaTime);
        void OnEvent(Event& e);

        OrthographicCamera& GetCamera() { return m_Camera; }
        const OrthographicCamera& GetCamera() const { return m_Camera; }

        const glm::vec3& GetPosition() const { return m_Camera.GetPosition(); }
        void SetPosition(const glm::vec3& position) { m_Camera.SetPosition(position); }

        float& GetRotation() { return m_Camera.GetRotation(); }
        const float& GetRotation() const { return m_Camera.GetRotation(); }
        void SetRotation(const float rotation) { m_Camera.SetRotation(rotation); }

        float& GetAspectRatio() { return m_AspectRatio; }
        const float& GetAspectRatio() const { return m_AspectRatio; }

        float& GetZoomLevel() { return m_ZoomLevel; }
        const float& GetZoomLevel() const { return m_ZoomLevel; }
        void SetZoomLevel(float zoomLevel)
        {
            m_ZoomLevel = zoomLevel;
            CalculateView();
        }

        OrthographicCameraBounds& GetBounds() { return m_Bounds; }
        void OnResize(float width, float height);

    private:
        void CalculateView();

        bool OnMouseScrolled(MouseScrolledEvent& e);
        bool OnWindowResize(WindowResizeEvent& e);

    private:
        float m_AspectRatio;
        float m_ZoomLevel = 1.0f;

        bool m_RotationEnabled;

    private:
        OrthographicCameraBounds m_Bounds;
        OrthographicCamera m_Camera;
        float m_TranslationSpeed = 5.0f, m_RotationSpeed = 180.0f;
    };
}

#endif // !_ORTHOGRAPHIC_CAMERA_CONTROLLER_H
