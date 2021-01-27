// Static Input declarations
// Each OS will have their own files creating the definitions
// that the linker will detect since all other platform specific
// code will be stripped out of other OS builds
// -------------------------------------------------------------

#ifndef _INPUT_H
#define _INPUT_H

#include "Bell/Base/Core.h"
#include "Bell/Base/Input/KeyCodes.h"
#include "Bell/Base/Input/MouseButtonCodes.h"

#include <variant>

namespace Bell
{
    // Stores the enum value for a key/mouse input
    struct KeyAlternative
    {
        // Type-safe union
        std::variant<Keys, Mouse> value;

        KeyAlternative() = default;
        KeyAlternative(const KeyAlternative &copy) = default;
        ~KeyAlternative() = default;

        KeyAlternative(Keys key) { value = key; }
        KeyAlternative(Mouse button) { value = button; }
    };

    class Input
    {
    public:
        // Raw keycode check
        // Doesn't take into account of remapping
        static bool IsKeyPressed(int keycode);
        // Raw mouse button check
        // Doesn't take into account of remapping
        static bool IsMouseButtonPressed(int button);
        // Raw mouse position X/Y check
        // Doesn't take into account of remapping
        static std::pair<float, float> GetMousePosition();
        // Raw mouse position X check
        // Doesn't take into account of remapping
        static float GetMouseX();
        // Raw mouse position Y check
        // Doesn't take into account of remapping
        static float GetMouseY();

        /// Input remapping functions

        // Checks to see if the key/button with identifier of name is pressed
        // Returns True if the key is being pressed this frame
        static bool IsInputPressed(const std::string &name);
        // Checks to see if the key/button that matches a KeyAlternative is pressed
        // Returns True if the key is being pressed this frame
        static bool IsInputPressed(KeyAlternative input);
        // Checks to see if the key/button that matches a KeyAlternative is pressed
        // Returns True if the key is being pressed this frame
        static bool IsMouseButtonPressed(Mouse button);
        // Takes in a name of the key and what Key/button is should be associated with
        // Will add the key/value pair to the mapping definitions if not already one there
        // Else it will replace the current value of the key with the new value
        static void Remap(const std::string &name, KeyAlternative input);

    private:
        // Map storing the key/value pairs for remapping keys and buttons
        static std::unordered_map<std::string, KeyAlternative> m_Mapping;
    };
} // namespace Bell

#endif // !_INPUT_H
