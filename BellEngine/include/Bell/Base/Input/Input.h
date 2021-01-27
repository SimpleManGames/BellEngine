// Input abstraction as a Singleton
// Each OS will have their own implemention inheriting from this
// -------------------------------------------------------------

#ifndef _INPUT_H
#define _INPUT_H

#include "Bell/Base/Core.h"
#include "Bell/Base/Input/KeyCodes.h"
#include "Bell/Base/Input/MouseButtonCodes.h"

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
        // Raw keycode check
        // Doesn't allow for remapping of keys
        static bool IsKeyPressed(int keycode);
        // Raw mouse button check
        // Doesn't allow for remapping of mouse buttons
        static bool IsMouseButtonPressed(int button);
        static std::pair<float, float> GetMousePosition();
        static float GetMouseX();
        static float GetMouseY();

        /// Input remapping functions
        
        // Checks to see if the key/button with identifier of name is pressed
        // Returns True if the key is being pressed this frame
        static bool IsInputPressed(const std::string &name);
        // Checks to see if the key/button that matches a KeyAlternative is pressed
        // Returns True if the key is being pressed this frame
        static bool IsInputPressed(KeyAlternative input);

        static bool IsMouseButtonPressed(Mouse button) { return IsMouseButtonPressed((int)button); }
        static void Remap(const std::string &name, KeyAlternative input) { m_Mapping[name] = input; }

    private:
        // Used for input remapping
        static std::unordered_map<std::string, KeyAlternative> m_Mapping;
    };
} // namespace Bell

#endif // !_INPUT_H
