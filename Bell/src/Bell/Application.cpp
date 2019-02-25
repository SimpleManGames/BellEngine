#include "bpch.h"
#include "Application.h"

#include "Bell/Log.h"

#include <glad/glad.h>

#include "Input.h"

namespace Bell {
    Application* Application::s_Instance = nullptr;

    Application::Application()
    {
        B_CORE_ASSERT(!s_Instance, "There is already an instance of Application");
        s_Instance = this;

        // Creates the unique pointer for our window
        m_Window = std::unique_ptr<Window>(Window::Create());
        // Sets the function we use for event handling
        m_Window->SetEventCallback(B_BIND_EVENT_FN(Application::OnEvent));
    }

    Application::~Application() { }

    void Application::OnEvent(Event & e)
    {
        // Makes a dispatcher
        EventDispatcher dispatcher(e);
        // Listens and acts on window close events using the defined OnWindowClose function
        dispatcher.Dispatch<WindowCloseEvent>(B_BIND_EVENT_FN(Application::OnWindowClose));

        // Reverse through the layers so the overlays get events before regular layers
        for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
        {
            (*--it)->OnEvent(e);
            if (e.Handled)
                break;
        }
    }

    void Application::Run()
    {
        while (m_Running)
        {
            glClearColor(0, 0.5, 0, 1);
            glClear(GL_COLOR_BUFFER_BIT);

            // Update each layer
            for (Layer* layer : m_LayerStack)
                layer->OnUpdate();

            auto[x, y] = Input::GetMousePosition();
            B_CORE_TRACE("{0}, {1}", x, y);

            m_Window->OnUpdate();
        }
    }

    bool Application::OnWindowClose(WindowCloseEvent& e)
    {
        m_Running = false;
        return false;
    }

    void Application::PushLayer(Layer * layer)
    {
        m_LayerStack.PushLayer(layer);
        layer->OnAttach();
    }

    void Application::PushOverlay(Layer * layer)
    {
        m_LayerStack.PushOverlay(layer);
        layer->OnAttach();
    }
}