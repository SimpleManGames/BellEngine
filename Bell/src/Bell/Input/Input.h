// Input abstraction as a Singleton
// Each OS will have their own implemention inheriting from this
// -------------------------------------------------------------

#ifndef _INPUT_H
#define _INPUT_H

#include "Bell/Core.h"

namespace Bell
{
    class BELL_API Input
    {
    public:
        // Singleton
        Input(const Input&) = delete;
        Input& operator=(const Input&) = delete;

        inline static bool IsKeyPressed(int keycode) { return  s_Instance->IsKeyPressedImpl(keycode); }
        
        inline static bool IsMouseButtonPressed(int button) { return s_Instance->IsMouseButtonPressedImpl(button); }
        inline static std::pair<float, float> GetMousePosition() { return s_Instance->GetMousePositionImpl(); }
        inline static float GetMouseX() { return s_Instance->GetMouseXImpl(); }
        inline static float GetMouseY() { return s_Instance->GetMouseYImpl(); }

    protected:
        // Protected so only inherited classes can create an Input
        Input() = default;

    protected:
        virtual bool IsKeyPressedImpl(int keycode) = 0;

        virtual bool IsMouseButtonPressedImpl(int button) = 0;
        virtual std::pair<float, float> GetMousePositionImpl() = 0;
        virtual float GetMouseXImpl() = 0;
        virtual float GetMouseYImpl() = 0;

    private:
        static Scope<Input> s_Instance;
    };
}

#endif // !_INPUT_H
