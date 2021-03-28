
// __MAIN_FILE__ is only to be defined once in the file that
// defines Bell::CreateApplication
#define __MAIN_FILE__
#include <Bell.h>

#include <Platform/OpenGL/OpenGLShader.h>

#include <imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "EditorLayer.h"

// Default class for entry point

namespace Bell
{
    class BellEditorApp : public Application
    {
    public:
        BellEditorApp()
            : Application(WindowProps("Bell Editor"))
        {
            InsertLayer(new Editor::EditorLayer());
        }
    };

    // Application side function for defining entry point
    Bell::Application *Bell::CreateApplication()
    {
        return new BellEditorApp();
    }
} // namespace Bell::Editor