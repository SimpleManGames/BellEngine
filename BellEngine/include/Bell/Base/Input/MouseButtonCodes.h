#ifndef _MOUSEBUTTONCODES_H
#define _MOUSEBUTTONCODES_H

namespace Bell
{
    enum class Mouse : int16_t
    {
        // From glfw3.h
        Button1 = 0,
        Button2 = 1,
        Button3 = 2,
        Button4 = 3,
        Button5 = 4,
        Button6 = 5,
        Button7 = 6,
        Button8 = 7,

        ButtonLeft = Button1,
        ButtonRight = Button2,
        ButtonMiddle = Button3,

        ButtonLast = Button8,
    };
}

// From glfw3.h

#define B_MOUSE_BUTTON_1      ::Bell::Mouse::Button1
#define B_MOUSE_BUTTON_2      ::Bell::Mouse::Button2
#define B_MOUSE_BUTTON_3      ::Bell::Mouse::Button3
#define B_MOUSE_BUTTON_4      ::Bell::Mouse::Button4
#define B_MOUSE_BUTTON_5      ::Bell::Mouse::Button5
#define B_MOUSE_BUTTON_6      ::Bell::Mouse::Button6
#define B_MOUSE_BUTTON_7      ::Bell::Mouse::Button7
#define B_MOUSE_BUTTON_8      ::Bell::Mouse::Button8
#define B_MOUSE_BUTTON_LAST   B_MOUSE_BUTTON_8
#define B_MOUSE_BUTTON_LEFT   B_MOUSE_BUTTON_1
#define B_MOUSE_BUTTON_RIGHT  B_MOUSE_BUTTON_2
#define B_MOUSE_BUTTON_MIDDLE B_MOUSE_BUTTON_3

#endif // !_MOUSEBUTTONCODES_H
