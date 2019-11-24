// Input abstraction as a Singleton
// Each OS will have their own implemention inheriting from this
// -------------------------------------------------------------

#ifndef _INPUT_H
#define _INPUT_H

#include "Bell/Core/Core.h"
#include "Bell/Core/Input/KeyCodes.h"
#include "Bell/Core/Input/MouseButtonCodes.h"

#include <variant>

namespace Bell
{
    struct KeyAlternative
    {
        // Type-safe union
        std::variant<Keys, Mouse> value;

        KeyAlternative() = default;
        KeyAlternative(Keys key) { value = key; }
        KeyAlternative(Mouse button) { value = button; }
    };

    class Input
    {
    public:
        // Singleton
        Input(const Input&) = delete;
        Input& operator=(const Input&) = delete;

        // Raw keycode check
        // Doesn't allow for remapping of keys
        inline static bool IsKeyPressed(int keycode) { return  s_Instance->IsKeyPressedImpl(keycode); }
        // Raw mouse button check
        // Doesn't allow for remapping of mouse buttons
        inline static bool IsMouseButtonPressed(int button) { return s_Instance->IsMouseButtonPressedImpl(button); }

        inline static std::pair<float, float> GetMousePosition() { return s_Instance->GetMousePositionImpl(); }
        inline static float GetMouseX() { return s_Instance->GetMouseXImpl(); }
        inline static float GetMouseY() { return s_Instance->GetMouseYImpl(); }
        
        /// Input remapping functions
        // Checks to see if the key/button with identifier of name is pressed
        inline static bool IsInputPressed(const std::string& name)
        {
            // Checks if that pair with 'name' exists
            if (s_Instance->m_Mapping.count(name) != 0)
            {
                return IsInputPressed(s_Instance->m_Mapping[name]);
            }

            B_CORE_WARN("The input {0} is not mapped!", name);
            return false;
        }
        inline static bool IsInputPressed(KeyAlternative input)
        {
            if (std::holds_alternative<Keys>(input.value))
                return s_Instance->IsKeyPressedImpl((int)std::get<Keys>(input.value));

            if (std::holds_alternative<Mouse>(input.value))
                return s_Instance->IsKeyPressedImpl((int)std::get<Mouse>(input.value));

            B_CORE_WARN("Unknown KeyAlternative Input");
            return false;
        }
        inline static bool IsMouseButtonPressed(Mouse button) { return s_Instance->IsMouseButtonPressedImpl((int)button); }

        inline static void Remap(const std::string& name, KeyAlternative input) { s_Instance->m_Mapping[name] = input; }

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
        // Used for input remapping
        std::unordered_map<std::string, KeyAlternative> m_Mapping;

        static Scope<Input> s_Instance;
    };
}

#endif // !_INPUT_H
