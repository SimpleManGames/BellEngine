#include "bpch.h"
#include "Application.h"

#include "Bell/Events/ApplicationEvent.h"
#include "Bell/Log.h"

#include <GLFW/glfw3.h>

namespace Bell {

    Application::Application() {
        m_Window = std::unique_ptr<Window>(Window::Create());
    }

    Application::~Application() { }

    void Application::Run()
    {
        while (m_Running)
        {
            m_Window->OnUpdate();
        }
    }
}