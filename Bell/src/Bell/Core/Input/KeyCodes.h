#ifndef _KEYCODES_H
#define _KEYCODES_H

namespace Bell
{
    enum class Keys : int16_t
    {
        // From glfw3.h
        Unknown = -1,

        Space =          32,
        Apostrophe =     39, /* ' */
        Comma =          44, /* , */
        Minus =          45, /* - */
        Period =         46, /* . */
        Slash =          47, /* / */
        D0 =             48,
        D1 =             49,
        D2 =             50,
        D3 =             51,
        D4 =             52,
        D5 =             53,
        D6 =             54,
        D7 =             55,
        D8 =             56,
        D9 =             57,
        Semicolon =      59, /* ; */
        Equal =          61, /* = */
        A =              65,
        B =              66,
        C =              67,
        D =              68,
        E =              69,
        F =              70,
        G =              71,
        H =              72,
        I =              73,
        J =              74,
        K =              75,
        L =              76,
        M =              77,
        N =              78,
        O =              79,
        P =              80,
        Q =              81,
        R =              82,
        S =              83,
        T =              84,
        U =              85,
        V =              86,
        W =              87,
        X =              88,
        Y =              89,
        Z =              90,
        LeftBracket =    91, /* [ */
        Backshash =      92, /* / */
        RightBracket =   93, /* ] */
        GraveAccent =    96, /* ` */
        World1 =         161, /* non-US #1 */
        World2 =         162, /* non-US #2 */
                         
        Escape =         256,
        Enter =          257,
        Tab =            258,
        Backspace =      259,
        Insert =         260,
        Delete =         261,
        Right =          262,
        Left =           263,
        Down =           264,
        Up =             265,
        PageUp =         266,
        PageDown =       267,
        Home =           268,
        End =            269,
        CapsLock =       280,
        ScrollLock =     281,
        NumLock =        282,
        PrintScreen =    283,
        Pause =          284,
        F1 =             290,
        F2 =             291,
        F3 =             292,
        F4 =             293,
        F5 =             294,
        F6 =             295,
        F7 =             296,
        F8 =             297,
        F9 =             298,
        F10 =            299,
        F11 =            300,
        F12 =            301,
        F13 =            302,
        F14 =            303,
        F15 =            304,
        F16 =            305,
        F17 =            306,
        F18 =            307,
        F19 =            308,
        F20 =            309,
        F21 =            310,
        F22 =            311,
        F23 =            312,
        F24 =            313,
        F25 =            314,
        Numpad0 =        320,
        Numpad1 =        321,
        Numpad2 =        322,
        Numpad3 =        323,
        Numpad4 =        324,
        Numpad5 =        325,
        Numpad6 =        326,
        Numpad7 =        327,
        Numpad8 =        328,
        Numpad9 =        329,
        NumpadDecimal =  330,
        NumpadDivide =   331,
        NumpadMultiply = 332,
        NumpadSubtract = 333,
        NumpadAdd =      334,
        NumpadEnter =    335,
        NumpadEqual =    336,
        LeftShift =      340,
        LeftControl =    341,
        LeftAlt =        342,
        LeftSuper =      343,
        RightShift =     344,
        RightControl =   345,
        RightAlt =       346,
        RightSuper =     347,
        Menu =           348,

        KeyLast =        Menu,
    };
}

// From glfw3.h

/* Printable keys */
#define B_KEY_SPACE         ::Bell::Keys::Space
#define B_KEY_APOSTROPHE    ::Bell::Keys::Apostrophe  /* ' */
#define B_KEY_COMMA         ::Bell::Keys::Comma  /* , */
#define B_KEY_MINUS         ::Bell::Keys::Minus  /* - */
#define B_KEY_PERIOD        ::Bell::Keys::Period  /* . */
#define B_KEY_SLASH         ::Bell::Keys::Slash  /* / */
#define B_KEY_0             ::Bell::Keys::D0
#define B_KEY_1             ::Bell::Keys::D1
#define B_KEY_2             ::Bell::Keys::D2
#define B_KEY_3             ::Bell::Keys::D3
#define B_KEY_4             ::Bell::Keys::D4
#define B_KEY_5             ::Bell::Keys::D5
#define B_KEY_6             ::Bell::Keys::D6
#define B_KEY_7             ::Bell::Keys::D7
#define B_KEY_8             ::Bell::Keys::D8
#define B_KEY_9             ::Bell::Keys::D9
#define B_KEY_SEMICOLON     ::Bell::Keys::Semicolon  /* ; */
#define B_KEY_EQUAL         ::Bell::Keys::Equal  /* = */
#define B_KEY_A             ::Bell::Keys::A
#define B_KEY_B             ::Bell::Keys::B
#define B_KEY_C             ::Bell::Keys::C
#define B_KEY_D             ::Bell::Keys::D
#define B_KEY_E             ::Bell::Keys::E
#define B_KEY_F             ::Bell::Keys::F
#define B_KEY_G             ::Bell::Keys::G
#define B_KEY_H             ::Bell::Keys::H
#define B_KEY_I             ::Bell::Keys::I
#define B_KEY_J             ::Bell::Keys::J
#define B_KEY_K             ::Bell::Keys::K
#define B_KEY_L             ::Bell::Keys::L
#define B_KEY_M             ::Bell::Keys::M
#define B_KEY_N             ::Bell::Keys::N
#define B_KEY_O             ::Bell::Keys::O
#define B_KEY_P             ::Bell::Keys::P
#define B_KEY_Q             ::Bell::Keys::Q
#define B_KEY_R             ::Bell::Keys::R
#define B_KEY_S             ::Bell::Keys::S
#define B_KEY_T             ::Bell::Keys::T
#define B_KEY_U             ::Bell::Keys::U
#define B_KEY_V             ::Bell::Keys::V
#define B_KEY_W             ::Bell::Keys::W
#define B_KEY_X             ::Bell::Keys::X
#define B_KEY_Y             ::Bell::Keys::Y
#define B_KEY_Z             ::Bell::Keys::Z
#define B_KEY_LEFT_BRACKET  ::Bell::Keys::LeftBracket  /* [ */
#define B_KEY_BACKSLASH     ::Bell::Keys::Backshash  /* \ */
#define B_KEY_RIGHT_BRACKET ::Bell::Keys::RightBracket  /* ] */
#define B_KEY_GRAVE_ACCENT  ::Bell::Keys::GraveAccent  /* ` */
#define B_KEY_WORLD_1       ::Bell::Keys::World1 /* non-US #1 */
#define B_KEY_WORLD_2       ::Bell::Keys::World2 /* non-US #2 */

/* Function keys */
#define B_KEY_ESCAPE        ::Bell::Keys::Escape
#define B_KEY_ENTER         ::Bell::Keys::Enter
#define B_KEY_TAB           ::Bell::Keys::Tab
#define B_KEY_BACKSPACE     ::Bell::Keys::Backspace
#define B_KEY_INSERT        ::Bell::Keys::Insert
#define B_KEY_DELETE        ::Bell::Keys::Delete
#define B_KEY_RIGHT         ::Bell::Keys::Right
#define B_KEY_LEFT          ::Bell::Keys::Left
#define B_KEY_DOWN          ::Bell::Keys::Down
#define B_KEY_UP            ::Bell::Keys::Up
#define B_KEY_PAGE_UP       ::Bell::Keys::PageUp
#define B_KEY_PAGE_DOWN     ::Bell::Keys::PageDown
#define B_KEY_HOME          ::Bell::Keys::Home
#define B_KEY_END           ::Bell::Keys::End
#define B_KEY_CAPS_LOCK     ::Bell::Keys::CapsLock
#define B_KEY_SCROLL_LOCK   ::Bell::Keys::ScrollLock
#define B_KEY_NUM_LOCK      ::Bell::Keys::NumLock
#define B_KEY_PRINT_SCREEN  ::Bell::Keys::PrintScreen
#define B_KEY_PAUSE         ::Bell::Keys::Pause
#define B_KEY_F1            ::Bell::Keys::F1 
#define B_KEY_F2            ::Bell::Keys::F2 
#define B_KEY_F3            ::Bell::Keys::F3 
#define B_KEY_F4            ::Bell::Keys::F4 
#define B_KEY_F5            ::Bell::Keys::F5 
#define B_KEY_F6            ::Bell::Keys::F6 
#define B_KEY_F7            ::Bell::Keys::F7 
#define B_KEY_F8            ::Bell::Keys::F8 
#define B_KEY_F9            ::Bell::Keys::F9 
#define B_KEY_F10           ::Bell::Keys::F10
#define B_KEY_F11           ::Bell::Keys::F11
#define B_KEY_F12           ::Bell::Keys::F12
#define B_KEY_F13           ::Bell::Keys::F13
#define B_KEY_F14           ::Bell::Keys::F14
#define B_KEY_F15           ::Bell::Keys::F15
#define B_KEY_F16           ::Bell::Keys::F16
#define B_KEY_F17           ::Bell::Keys::F17
#define B_KEY_F18           ::Bell::Keys::F18
#define B_KEY_F19           ::Bell::Keys::F19
#define B_KEY_F20           ::Bell::Keys::F20
#define B_KEY_F21           ::Bell::Keys::F21
#define B_KEY_F22           ::Bell::Keys::F22
#define B_KEY_F23           ::Bell::Keys::F23
#define B_KEY_F24           ::Bell::Keys::F24
#define B_KEY_F25           ::Bell::Keys::F25
#define B_KEY_KP_0          ::Bell::Keys::Numpad0
#define B_KEY_KP_1          ::Bell::Keys::Numpad1
#define B_KEY_KP_2          ::Bell::Keys::Numpad2
#define B_KEY_KP_3          ::Bell::Keys::Numpad3
#define B_KEY_KP_4          ::Bell::Keys::Numpad4
#define B_KEY_KP_5          ::Bell::Keys::Numpad5
#define B_KEY_KP_6          ::Bell::Keys::Numpad6
#define B_KEY_KP_7          ::Bell::Keys::Numpad7
#define B_KEY_KP_8          ::Bell::Keys::Numpad8
#define B_KEY_KP_9          ::Bell::Keys::Numpad9
#define B_KEY_KP_DECIMAL    ::Bell::Keys::NumpadDecimal
#define B_KEY_KP_DIVIDE     ::Bell::Keys::NumpadDivide
#define B_KEY_KP_MULTIPLY   ::Bell::Keys::NumpadMultiply
#define B_KEY_KP_SUBTRACT   ::Bell::Keys::NumpadSubtract
#define B_KEY_KP_ADD        ::Bell::Keys::NumpadAdd
#define B_KEY_KP_ENTER      ::Bell::Keys::NumpadEnter
#define B_KEY_KP_EQUAL      ::Bell::Keys::NumpadEqual
#define B_KEY_LEFT_SHIFT    ::Bell::Keys::LeftShift
#define B_KEY_LEFT_CONTROL  ::Bell::Keys::LeftControl
#define B_KEY_LEFT_ALT      ::Bell::Keys::LeftAlt
#define B_KEY_LEFT_SUPER    ::Bell::Keys::LeftSuper
#define B_KEY_RIGHT_SHIFT   ::Bell::Keys::RightShift
#define B_KEY_RIGHT_CONTROL ::Bell::Keys::RightControl
#define B_KEY_RIGHT_ALT     ::Bell::Keys::RightAlt
#define B_KEY_RIGHT_SUPER   ::Bell::Keys::RightSuper
#define B_KEY_MENU          ::Bell::Keys::Menu

#define B_KEY_LAST          ::Bell::Keys::Menu


#endif // !_KEYCODES_H
