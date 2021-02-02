/**
 * @file Input.h
 * @brief Static Input declarations
 * Each OS will have their own files creating the definitions
 * that the linker will detect since all other platform specific
 * code will be stripped out of other OS builds
 * 
 */

#ifndef _INPUT_H
#define _INPUT_H

#include "Bell/Base/Core.h"
#include "Bell/Base/Input/KeyCodes.h"
#include "Bell/Base/Input/MouseButtonCodes.h"

#include <variant>

namespace Bell
{
    /**
     * @brief Stores the enum value for a key/mouse input
     * 
     */
    struct KeyAlternative
    {
        /**
         * @brief Enum value of the key code stored in a type safe union
         * 
         */
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
        /**
         * @brief Raw keycode check
         * Doesn't take into account of remapping
         * 
         * @param keycode Key Code value
         * @return true If the key was pressed this frame
         * @return false If the key wasn't pressed
         */
        static bool IsKeyPressed(int keycode);
        /**
         * @brief Raw mouse button check
         * Doesn't take into account of remapping
         * 
         * @param button Button Code value
         * @return true If the Button was pressed this frame
         * @return false If the Button wasn't pressed
         */
        static bool IsMouseButtonPressed(int button);
        /**
         * @brief Get the Mouse Position object
         * Raw mouse position X/Y check
         * Doesn't take into account of remapping
         * 
         * @return std::pair<float, float> Screen space X and Y coordinate
         */
        static std::pair<float, float> GetMousePosition();
        /**
         * @brief Get the Mouse X object
         * Raw mouse position X Coord
         * Doesn't take into account of remapping
         * 
         * @return float Screen space X coordinate
         */
        static float GetMouseX();
        /**
         * @brief Get the Mouse Y Coord
         * Raw mouse position Y check
         * Doesn't take into account of remapping
         * 
         * @return float Screen space Y coordinate
         */
        static float GetMouseY();

        /// Input remapping functions

        /**
         * @brief Checks to see if the key/button with identifier of name is pressed
         * 
         * @param name Key value for the input we are checking
         * @return Wether or not the value for key is pressed this frame
         */
        static bool IsInputPressed(const std::string &name);
        /**
         * @brief Checks to see if the key/button that matches a KeyAlternative is pressed
         * 
         * @param input Key input to check for the input being pressed
         * @return Wether or not the value for the key alternative is pressed this frame
         */
        static bool IsInputPressed(KeyAlternative input);
        /**
         * @brief Checks to see if the key/button that matches a KeyAlternative is pressed
         * 
         * @param button Mouse code that we want to chekc
         * @return Wether or not the mouse button was pressed this frame
         */
        static bool IsMouseButtonPressed(Mouse button);
        /**
         * @brief Takes in a name of the key and what Key/button is should be associated with.
         * Will add the key/value pair to the mapping definitions if not already one there,
         * Else it will replace the current value of the key with the new value
         * 
         * @param name Name that we can use to look up the input
         * @param input Key code wrapped in the type safe union
         */
        static void Remap(const std::string &name, KeyAlternative input);

    private:
        /**
         * @brief Map storing the key/value pairs for remapping keys and buttons
         * 
         */
        static std::unordered_map<std::string, KeyAlternative> m_Mapping;
    };
} // namespace Bell

#endif // !_INPUT_H
