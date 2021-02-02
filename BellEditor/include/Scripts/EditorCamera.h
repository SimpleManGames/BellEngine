#ifndef EDITORCAMERA_H
#define EDITORCAMERA_H

#include <Bell.h>

namespace Bell::Editor
{
    class EditorCamera : public ScriptableEntity
    {
    public:
        void OnCreate()
        {
            Input::Remap("camera_move_left", KeyAlternative(Keys::A));
            Input::Remap("camera_move_right", KeyAlternative(Keys::D));
            Input::Remap("camera_move_up", KeyAlternative(Keys::W));
            Input::Remap("camera_move_down", KeyAlternative(Keys::S));
        }
        void OnDestroy()
        {
        }

        void OnUpdate(Timestep deltaTime)
        {
            auto &transform = GetComponent<TransformComponent>();

            if (Input::IsInputPressed("camera_move_left"))
            {
                transform.X() -= m_MoveSpeed * deltaTime;
            }
            if (Input::IsInputPressed("camera_move_right"))
            {
                transform.X() += m_MoveSpeed * deltaTime;
            }

            if (Input::IsInputPressed("camera_move_up"))
            {
                transform.Y() += m_MoveSpeed * deltaTime;
            }
            if (Input::IsInputPressed("camera_move_down"))
            {
                transform.Y() -= m_MoveSpeed * deltaTime;
            }
        }

    private:
        float m_MoveSpeed = 5.0f;
    };
} // namespace Bell::Editor

#endif // EDITORCAMERA_H