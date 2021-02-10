#ifndef SCENECAMERA_H
#define SCENECAMERA_H

#include "Bell/Renderer/Camera/Camera.h"

namespace Bell
{
    /**
     * @brief Camera used within Scenes
     * 
     * This class supplies common functionally that would be needed
     * for handling and controlling cameras
     * 
     */
    class SceneCamera : public Camera
    {
    public:
        /**
         * @brief Defines all the support camera projection types
         * 
         */
        enum class ProjectionType
        {
            Perspective = 0,
            Orthographic = 1
        };

        SceneCamera();
        virtual ~SceneCamera() = default;

        /**
         * @brief Set the Viewport Size based on width and height 
         * to calculate aspect ratio
         * 
         * @param width New Width
         * @param height New Height
         */
        void SetViewportSize(uint32_t width, uint32_t height);

#pragma region Perspective
        /**
         * @brief Set the Perspective values
         * 
         * @param verticalFOV New Perspective Vertival FOV
         * @param nearClip New Near Clip Plane
         * @param farClip New Far Clip Plane
         */
        void SetPerspective(float verticalFOV, float nearClip, float farClip);
        /**
         * @brief Get the Perspective Size
         * 
         * @return float Size
         */
        float GetPerspectiveVerticalFOV() const { return m_PerspectiveFOV; }
        /**
         * @brief Set the Perspective Size
         * 
         * @param size New size
         */
        void SetPerspectiveVerticalFOV(float size)
        {
            m_PerspectiveFOV = size;
            RecalculateProject();
        }
        /**
         * @brief Get the Perspective Near Clip value
         * 
         * @return float Near Clip value
         */
        float GetPerspectiveNearClip() const { return m_PerspectiveNear; }
        /**
         * @brief Set the Perspective Near Clip value
         * 
         * @param value New Value
         */
        void SetPerspectiveNearClip(float value)
        {
            m_PerspectiveNear = value;
            RecalculateProject();
        }
        /**
         * @brief Get the Perspective Far Clip value
         * 
         * @return float Far Clip value
         */
        float GetPerspectiveFarClip() const { return m_PerspectiveFar; }
        /**
         * @brief Set the Perspective Far Clip value
         * 
         * @param value New Value
         */
        void SetPerspectiveFarClip(float value)
        {
            m_PerspectiveFar = value;
            RecalculateProject();
        }
#pragma endregion // Perspective
#pragma region Orthographic

        /**
         * @brief Set the Orthographic values
         * 
         * @param size New Orthographic Size
         * @param nearClip New Near Clip Plane
         * @param farClip New Far Clip Plane
         */
        void SetOrthographic(float size, float nearClip, float farClip);
        /**
         * @brief Get the Orthographic Size
         * 
         * @return float Size
         */
        float GetOrthographicSize() const { return m_OrthographicSize; }
        /**
         * @brief Set the Orthographic Size
         * 
         * @param size New size
         */
        void SetOrthographicSize(float size)
        {
            m_OrthographicSize = size;
            RecalculateProject();
        }

        /**
         * @brief Get the Orthographic Near Clip value
         * 
         * @return float Near Clip value
         */
        float GetOrthographicNearClip() const { return m_OrthographicNear; }
        /**
         * @brief Set the Orthographic Near Clip value
         * 
         * @param value New Value
         */
        void SetOrthographicNearClip(float value)
        {
            m_OrthographicNear = value;
            RecalculateProject();
        }
        /**
         * @brief Get the Orthographic Far Clip value
         * 
         * @return float Far Clip value
         */
        float GetOrthographicFarClip() const { return m_OrthographicFar; }
        /**
         * @brief Set the Orthographic Far Clip value
         * 
         * @param value New Value
         */
        void SetOrthographicFarClip(float value)
        {
            m_OrthographicFar = value;
            RecalculateProject();
        }
#pragma endregion // Orthographic

        /**
         * @brief Get the Projection Type this camera uses
         * 
         * @return ProjectionType This camera's type
         */
        ProjectionType GetProjectionType() const { return m_ProjectionType; }
        /**
         * @brief Set the Projection Type for this camera
         * 
         * @param type New Projection Type
         */
        void SetProjectionType(ProjectionType type)
        {
            m_ProjectionType = type;
            RecalculateProject();
        }

    private:
        ProjectionType m_ProjectionType = ProjectionType::Orthographic;
        /**
         * @brief Relcaluates the projection matrix with values the known values
         * 
         */
        void RecalculateProject();

        float m_PerspectiveFOV = glm::radians(45.0f);
        float m_PerspectiveNear = 0.01f, m_PerspectiveFar = 1000.0f;

        float m_OrthographicSize = 10.0f;
        float m_OrthographicNear = 0.0f, m_OrthographicFar = 1.0f;

        float m_AspectRatio = 0.0f;
    };
} // namespace Bell

#endif // SCENECAMERA_H