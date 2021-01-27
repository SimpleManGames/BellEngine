#include "bpch.h"
#include "Bell/Base/Input/Input.h"

#include "Bell/Base/Application.h"
#include <GLFW/glfw3.h>

namespace Bell
{
    std::unordered_map<std::string, KeyAlternative> Input::m_Mapping = {};

    bool Input::IsKeyPressed(int keycode)
    {
        auto window = static_cast<GLFWwindow *>(Application::Get().GetWindow().GetNativeWindow());
        auto state = glfwGetKey(window, keycode);
        return state == GLFW_PRESS || state == GLFW_REPEAT;
    }

    bool Input::IsMouseButtonPressed(int button)
    {
        auto window = static_cast<GLFWwindow *>(Application::Get().GetWindow().GetNativeWindow());
        auto state = glfwGetMouseButton(window, button);

        return state == GLFW_PRESS;
    }

    std::pair<float, float> Input::GetMousePosition()
    {
        auto window = static_cast<GLFWwindow *>(Application::Get().GetWindow().GetNativeWindow());
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);

        return {(float)xpos, (float)ypos};
    }

    float Input::GetMouseX()
    {
        auto [x, y] = GetMousePosition();
        return x;
    }

    float Input::GetMouseY()
    {
        auto [x, y] = GetMousePosition();
        return y;
    }

    bool Input::IsInputPressed(KeyAlternative input)
    {
        if (std::holds_alternative<Keys>(input.value))
            return IsKeyPressed((int)std::get<Keys>(input.value));

        if (std::holds_alternative<Mouse>(input.value))
            return IsKeyPressed((int)std::get<Mouse>(input.value));

        B_CORE_WARN("Unknown KeyAlternative Input");
        return false;
    }

    bool Input::IsInputPressed(const std::string &name)
    {
        // Checks if that pair with 'name' exists
        if (m_Mapping.count(name) != 0)
        {
            return IsInputPressed(m_Mapping[name]);
        }

        B_CORE_WARN("The input {0} is not mapped!", name);
        return false;
    }

    bool Input::IsMouseButtonPressed(Mouse button)
    {
        return IsMouseButtonPressed((int)button);
    }

    void Input::Remap(const std::string &name, KeyAlternative input)
    {
        m_Mapping[name] = input;
    }

} // namespace Bell