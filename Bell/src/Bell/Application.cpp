#include "bpch.h"
#include "Application.h"

#include "Bell/Log.h"

#include "Bell/Renderer/Renderer.h"

#include "Input.h"

#include <GLFW/glfw3.h>

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
        m_Window->SetVSync(true);

        Renderer::Init();

        m_ImGuiLayer = new ImGuiLayer();
        PushOverlay(m_ImGuiLayer);
    }

    Application::~Application() {}

    void Application::OnEvent(Event& e) {
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

    void Application::Run() {
        while (m_Running)
        {
            // Calculate delta time
            float time = (float)glfwGetTime();
            Timestep deltaTime = time - m_LastFrameTime;
            m_LastFrameTime = time;

            // Update each layer
            for (Layer* layer : m_LayerStack)
                layer->OnUpdate(deltaTime);

            m_ImGuiLayer->Begin();
            for (Layer* layer : m_LayerStack)
                layer->OnImGuiRender();
            m_ImGuiLayer->End();

            m_Window->OnUpdate();
        }
    }

    bool Application::OnWindowClose(WindowCloseEvent& e) {
        m_Running = false;
        return false;
    }

    void Application::PushLayer(Layer* layer) {
        m_LayerStack.PushLayer(layer);
        layer->OnAttach();
    }

    void Application::PushOverlay(Layer* layer) {
        m_LayerStack.PushOverlay(layer);
        layer->OnAttach();
    }
}