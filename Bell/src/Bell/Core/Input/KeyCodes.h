#ifndef _KEYCODES_H
#define _KEYCODES_H

namespace Bell
{
    enum class Keys
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
#define B_KEY_SPACE         32
#define B_KEY_APOSTROPHE    39  /* ' */
#define B_KEY_COMMA         44  /* , */
#define B_KEY_MINUS         45  /* - */
#define B_KEY_PERIOD        46  /* . */
#define B_KEY_SLASH         47  /* / */
#define B_KEY_0             48
#define B_KEY_1             49
#define B_KEY_2             50
#define B_KEY_3             51
#define B_KEY_4             52
#define B_KEY_5             53
#define B_KEY_6             54
#define B_KEY_7             55
#define B_KEY_8             56
#define B_KEY_9             57
#define B_KEY_SEMICOLON     59  /* ; */
#define B_KEY_EQUAL         61  /* = */
#define B_KEY_A             65
#define B_KEY_B             66
#define B_KEY_C             67
#define B_KEY_D             68
#define B_KEY_E             69
#define B_KEY_F             70
#define B_KEY_G             71
#define B_KEY_H             72
#define B_KEY_I             73
#define B_KEY_J             74
#define B_KEY_K             75
#define B_KEY_L             76
#define B_KEY_M             77
#define B_KEY_N             78
#define B_KEY_O             79
#define B_KEY_P             80
#define B_KEY_Q             81
#define B_KEY_R             82
#define B_KEY_S             83
#define B_KEY_T             84
#define B_KEY_U             85
#define B_KEY_V             86
#define B_KEY_W             87
#define B_KEY_X             88
#define B_KEY_Y             89
#define B_KEY_Z             90
#define B_KEY_LEFT_BRACKET  91  /* [ */
#define B_KEY_BACKSLASH     92  /* \ */
#define B_KEY_RIGHT_BRACKET 93  /* ] */
#define B_KEY_GRAVE_ACCENT  96  /* ` */
#define B_KEY_WORLD_1       161 /* non-US #1 */
#define B_KEY_WORLD_2       162 /* non-US #2 */

/* Function keys */
#define B_KEY_ESCAPE        256
#define B_KEY_ENTER         257
#define B_KEY_TAB           258
#define B_KEY_BACKSPACE     259
#define B_KEY_INSERT        260
#define B_KEY_DELETE        261
#define B_KEY_RIGHT         262
#define B_KEY_LEFT          263
#define B_KEY_DOWN          264
#define B_KEY_UP            265
#define B_KEY_PAGE_UP       266
#define B_KEY_PAGE_DOWN     267
#define B_KEY_HOME          268
#define B_KEY_END           269
#define B_KEY_CAPS_LOCK     280
#define B_KEY_SCROLL_LOCK   281
#define B_KEY_NUM_LOCK      282
#define B_KEY_PRINT_SCREEN  283
#define B_KEY_PAUSE         284
#define B_KEY_F1            290
#define B_KEY_F2            291
#define B_KEY_F3            292
#define B_KEY_F4            293
#define B_KEY_F5            294
#define B_KEY_F6            295
#define B_KEY_F7            296
#define B_KEY_F8            297
#define B_KEY_F9            298
#define B_KEY_F10           299
#define B_KEY_F11           300
#define B_KEY_F12           301
#define B_KEY_F13           302
#define B_KEY_F14           303
#define B_KEY_F15           304
#define B_KEY_F16           305
#define B_KEY_F17           306
#define B_KEY_F18           307
#define B_KEY_F19           308
#define B_KEY_F20           309
#define B_KEY_F21           310
#define B_KEY_F22           311
#define B_KEY_F23           312
#define B_KEY_F24           313
#define B_KEY_F25           314
#define B_KEY_KP_0          320
#define B_KEY_KP_1          321
#define B_KEY_KP_2          322
#define B_KEY_KP_3          323
#define B_KEY_KP_4          324
#define B_KEY_KP_5          325
#define B_KEY_KP_6          326
#define B_KEY_KP_7          327
#define B_KEY_KP_8          328
#define B_KEY_KP_9          329
#define B_KEY_KP_DECIMAL    330
#define B_KEY_KP_DIVIDE     331
#define B_KEY_KP_MULTIPLY   332
#define B_KEY_KP_SUBTRACT   333
#define B_KEY_KP_ADD        334
#define B_KEY_KP_ENTER      335
#define B_KEY_KP_EQUAL      336
#define B_KEY_LEFT_SHIFT    340
#define B_KEY_LEFT_CONTROL  341
#define B_KEY_LEFT_ALT      342
#define B_KEY_LEFT_SUPER    343
#define B_KEY_RIGHT_SHIFT   344
#define B_KEY_RIGHT_CONTROL 345
#define B_KEY_RIGHT_ALT     346
#define B_KEY_RIGHT_SUPER   347
#define B_KEY_MENU          348

#define B_KEY_LAST               B_KEY_MENU


#endif // !_KEYCODES_H
