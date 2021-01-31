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
        SceneCamera();
        virtual ~SceneCamera() = default;

        /**
         * @brief Set the Orthographic values
         * 
         * @param size New Orthographic Size
         * @param nearClip New Near Clip Plane
         * @param farClip New Far Clip Plane
         */
        void SetOrthographic(float size, float nearClip, float farClip);
        /**
         * @brief Set the Viewport Size based on width and height 
         * to calculate aspect ratio
         * 
         * @param width New Width
         * @param height New Height
         */
        void SetViewportSize(uint32_t width, uint32_t height);

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
        void SetOrthographicSize(float size) { m_OrthographicSize = size; RecalculateProject();}

    private:
        /**
         * @brief Relcaluates the projection matrix with values the known values
         * 
         */
        void RecalculateProject();

        float m_OrthographicSize = 10.0f;
        float m_OrthographicNear = -1.0f, m_OrthographicFar = 1.0f;

        float m_AspectRatio = 0.0f;
    };
} // namespace Bell

#endif // SCENECAMERA_H