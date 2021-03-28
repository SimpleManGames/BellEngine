
// __MAIN_FILE__ is only to be defined once in the file that
// defines Bell::CreateApplication
#define __MAIN_FILE__
#include <Bell.h>

#include <Platform/OpenGL/OpenGLShader.h>

#include <imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Sandbox2D.h"

// Default class for entry point

class Sandbox : public Bell::Application
{
public:
    Sandbox()
        : Application({})
    {
        InsertLayer(new Sandbox2D());
    }
};

// Application side function for defining entry point
Bell::Application* Bell::CreateApplication()
{
    return new Sandbox();
}