// Windows Implementation of Input
// -------------------------------

#ifndef WINDOWS_INPUT_H
#define WINDOWS_INPUT_H

#include "Bell/Input.h"

namespace Bell
{
    class WindowsInput : public Input
    {
    protected:
        virtual bool IsKeyPressedImpl(int keycode) override;

        virtual bool IsMouseButtonPressedImpl(int button) override;
        virtual std::pair<float, float> GetMousePositionImpl() override;
        virtual float GetMouseXImpl() override;
        virtual float GetMouseYImpl() override;
    };
}

#endif // !WINDOWS_INPUT_H
