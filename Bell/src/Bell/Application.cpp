#include "bpch.h"
#include "Application.h"

#include "Bell/Log.h"

#include <GLFW/glfw3.h>

namespace Bell {

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

    Application::Application() 
    {
        // Creates the unique pointer for our window
        m_Window = std::unique_ptr<Window>(Window::Create());
        // Sets the function we use for event handling
        m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));
    }

    Application::~Application() { }

    void Application::OnEvent(Event & e)
    {
        // Makes a dispatcher
        EventDispatcher dispatcher(e);
        // Listens and acts on window close events using the defined OnWindowClose function
        dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));

        // Output the events that are currently happening to the console
        B_CORE_TRACE("{0}", e);
    }

    void Application::Run()
    {
        while (m_Running)
        {
            m_Window->OnUpdate();
        }
    }

    bool Application::OnWindowClose(WindowCloseEvent& e)
    {
        m_Running = false;
        return false;
    }
}