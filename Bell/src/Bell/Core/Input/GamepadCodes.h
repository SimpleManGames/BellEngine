#ifndef _GAMEPADCODES_H
#define _GAMEPADCODES_H

namespace Bell
{
    // From glfw3.h
    typedef enum class Joystick : int16_t
    {
        J1, G1 = 0,
        J2, G2 = 1,
        J3, G3 = 2,
        J4, G4 = 3,
        J5, G5 = 4,
        J6, G6 = 5,
        J7, G7 = 6,
        J8, G8 = 7,
        J9, G9 = 8,
        J10, G10 = 9,
        J11, G11 = 10,
        J12, G12 = 11,
        J13, G13 = 12,
        J14, G14 = 13,
        J15, G15 = 14,
        J16, G16 = 15,
        Last = J16,
    } Gamepad;
    //typedef Iterator<Joystick, Joystick::J1, Joystick::Last> JoystickIterator;

    /// May want to these enums later
    typedef enum class GamepadButtons : int16_t
    {
        A = 0,
        B = 1,
        X = 2,
        Y = 3,
        Left_Bumper = 4,
        Right_Bumper = 5,
        Back = 6,
        Start = 7,
        Guide = 8,
        Left_Thumb = 9,
        Right_Thumb = 10,
        Dpad_Up = 11,
        Dpad_Right = 12,
        Dpad_Down = 13,
        Dpad_Left = 14,
        Last = Dpad_Left,

        Cross = A,
        Circle = B,
        Square = X,
        Triangle = Y
    } GamepadButton;

    typedef enum class GamepadAxes : int16_t
    {
        Left_X = 0,
        Left_Y = 1,
        Right_X = 2,
        Right_Y = 3,
        Left_Trigger = 4,
        Right_Trigger = 5,
        Last = Right_Trigger
    } GamepadAxis;
}

#pragma region Joystick/Gamepad Def
#define B_JOYSTICK_1    ::Bell::Joystick::1
#define B_JOYSTICK_2    ::Bell::Joystick::2
#define B_JOYSTICK_3    ::Bell::Joystick::3
#define B_JOYSTICK_4    ::Bell::Joystick::4
#define B_JOYSTICK_5    ::Bell::Joystick::5
#define B_JOYSTICK_6    ::Bell::Joystick::6
#define B_JOYSTICK_7    ::Bell::Joystick::7
#define B_JOYSTICK_8    ::Bell::Joystick::8
#define B_JOYSTICK_9    ::Bell::Joystick::9
#define B_JOYSTICK_10   ::Bell::Joystick::10
#define B_JOYSTICK_11   ::Bell::Joystick::11
#define B_JOYSTICK_12   ::Bell::Joystick::12
#define B_JOYSTICK_13   ::Bell::Joystick::13
#define B_JOYSTICK_14   ::Bell::Joystick::14
#define B_JOYSTICK_15   ::Bell::Joystick::15
#define B_JOYSTICK_16   ::Bell::Joystick::16
#define B_JOYSTICK_LAST ::Bell::Joystick::Last

#define B_GAMEPAD_1    ::Bell::Gamepad::1
#define B_GAMEPAD_2    ::Bell::Gamepad::2
#define B_GAMEPAD_3    ::Bell::Gamepad::3
#define B_GAMEPAD_4    ::Bell::Gamepad::4
#define B_GAMEPAD_5    ::Bell::Gamepad::5
#define B_GAMEPAD_6    ::Bell::Gamepad::6
#define B_GAMEPAD_7    ::Bell::Gamepad::7
#define B_GAMEPAD_8    ::Bell::Gamepad::8
#define B_GAMEPAD_9    ::Bell::Gamepad::9
#define B_GAMEPAD_10   ::Bell::Gamepad::10
#define B_GAMEPAD_11   ::Bell::Gamepad::11
#define B_GAMEPAD_12   ::Bell::Gamepad::12
#define B_GAMEPAD_13   ::Bell::Gamepad::13
#define B_GAMEPAD_14   ::Bell::Gamepad::14
#define B_GAMEPAD_15   ::Bell::Gamepad::15
#define B_GAMEPAD_16   ::Bell::Gamepad::16
#define B_GAMEPAD_LAST ::Bell::Gamepad::Last
#pragma endregion 

#pragma region Gamepad Button Def
#define B_GAMEPAD_BUTTON_A               ::Bell::GamepadButton::A
#define B_GAMEPAD_BUTTON_B               ::Bell::GamepadButton::B
#define B_GAMEPAD_BUTTON_X               ::Bell::GamepadButton::X
#define B_GAMEPAD_BUTTON_Y               ::Bell::GamepadButton::Y
#define B_GAMEPAD_BUTTON_LEFT_BUMPER     ::Bell::GamepadButton::Left_Bumper
#define B_GAMEPAD_BUTTON_RIGHT_BUMPER    ::Bell::GamepadButton::Right_Bumper
#define B_GAMEPAD_BUTTON_BACK            ::Bell::GamepadButton::Back
#define B_GAMEPAD_BUTTON_START           ::Bell::GamepadButton::Start
#define B_GAMEPAD_BUTTON_GUIDE           ::Bell::GamepadButton::Guide
#define B_GAMEPAD_BUTTON_LEFT_THUMB      ::Bell::GamepadButton::Left_Thumb
#define B_GAMEPAD_BUTTON_RIGHT_THUMB     ::Bell::GamepadButton::Right_Thumb
#define B_GAMEPAD_BUTTON_DPAD_UP         ::Bell::GamepadButton::Dpad_Up
#define B_GAMEPAD_BUTTON_DPAD_RIGHT      ::Bell::GamepadButton::Dpad_Right
#define B_GAMEPAD_BUTTON_DPAD_DOWN       ::Bell::GamepadButton::Dpad_Down
#define B_GAMEPAD_BUTTON_DPAD_LEFT       ::Bell::GamepadButton::Dpad_Left
#define B_GAMEPAD_BUTTON_LAST            ::Bell::GamepadButton::Last

#define B_GAMEPAD_BUTTON_CROSS       B_GAMEPAD_BUTTON_A
#define B_GAMEPAD_BUTTON_CIRCLE      B_GAMEPAD_BUTTON_B
#define B_GAMEPAD_BUTTON_SQUARE      B_GAMEPAD_BUTTON_X
#define B_GAMEPAD_BUTTON_TRIANGLE    B_GAMEPAD_BUTTON_Y
#pragma endregion

#pragma region Gamepad Axes Def
#define B_GAMEPAD_AXIS_LEFT_X        ::Bell::GamepadAxis::Left_X
#define B_GAMEPAD_AXIS_LEFT_Y        ::Bell::GamepadAxis::Left_Y
#define B_GAMEPAD_AXIS_RIGHT_X       ::Bell::GamepadAxis::Right_X
#define B_GAMEPAD_AXIS_RIGHT_Y       ::Bell::GamepadAxis::Right_Y
#define B_GAMEPAD_AXIS_LEFT_TRIGGER  ::Bell::GamepadAxis::Left_Trigger
#define B_GAMEPAD_AXIS_RIGHT_TRIGGER ::Bell::GamepadAxis::Right_Trigger
#define B_GAMEPAD_AXIS_LAST          ::Bell::GamepadAxis::Last
#pragma endregion

#endif // !_GAMEPADCODES_H