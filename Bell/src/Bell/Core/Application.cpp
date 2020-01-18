#include "bpch.h"
#include "Application.h"

#include "Bell/Core/Log.h"

#include "Bell/Renderer/Renderer.h"
#include "Input/Input.h"

#include "Bell/Networking/Network.h"

#include <GLFW/glfw3.h>

namespace Bell
{
    Application* Application::s_Instance = nullptr;

    Application::Application()
    {
        Init();
    }

    Application::~Application() {
        m_ApplicationState = ApplicationState::Destroying;

        Renderer::Shutdown();
    }

    void Application::Init()
    {
        B_PROFILE_FUNCTION();
        {
            B_PROFILE_SCOPE("Application Construction");
            m_ApplicationState = ApplicationState::Constructing;
            B_CORE_ASSERT(!s_Instance, "There is already an instance of Application");
            s_Instance = this;
        }

        {
            B_PROFILE_SCOPE("Application Initializing");
            m_ApplicationState = ApplicationState::Initializing;

            {
                B_CORE_INFO("Bell Engine Initializing");

                Network::Init();
#ifdef B_CLIENT
                // Creates the unique pointer for our window
                {
                    B_PROFILE_SCOPE("Window Creation");
                    m_Window = Window::Create();
                    // Sets the function we use for event handling
                    m_Window->SetEventCallback(B_BIND_EVENT_FN(Application::OnEvent));
                    m_Window->SetVSync(false);
                }

                {
                    B_PROFILE_SCOPE("Renderer Init");
                    B_CORE_INFO("Renderer Initializing");
                    Renderer::Init();
                }
#endif

#ifdef B_SERVER
                {
                    B_PROFILE_SCOPE("Network Init");
                    B_CORE_INFO("Network Initializing");
                }
#endif
            }
        }

#if defined(B_DEBUG) && defined(B_CLIENT)
        {
            B_PROFILE_SCOPE("ImGuiLayer Creation");
            m_ImGuiLayer = new ImGuiLayer();
            PushOverlay(m_ImGuiLayer);
        }
#endif
    }

    void Application::OnEvent(Event& e) {
        B_PROFILE_FUNCTION();
        // Makes a dispatcher
        EventDispatcher dispatcher(e);
        // Listens and acts on window close events using the defined OnWindowClose function
        dispatcher.Dispatch<WindowCloseEvent>(B_BIND_EVENT_FN(Application::OnWindowClose));
        dispatcher.Dispatch<WindowResizeEvent>(B_BIND_EVENT_FN(Application::OnWindowResize));

        // Reverse through the layers so the overlays get events before regular layers
        for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
        {
            (*--it)->OnEvent(e);
            if (e.Handled)
                break;
        }
    }

    void Application::Run() {
        B_PROFILE_FUNCTION();
        m_ApplicationState = ApplicationState::Running;

        while (m_ApplicationState == ApplicationState::Running
            || m_ApplicationState == ApplicationState::Minimized)
        {
            B_PROFILE_SCOPE("Run Loop");

            // Calculate delta time
            float time = (float)glfwGetTime();
            Timestep deltaTime = time - m_LastFrameTime;
            m_LastFrameTime = time;

            if (!(m_ApplicationState == ApplicationState::Minimized))
            {
                // Update each layer
                for (Layer* layer : m_LayerStack)
                {
                    B_PROFILE_SCOPE(layer->GetName().c_str());
                    layer->OnUpdate(deltaTime);
                }
            }

#ifdef B_DEBUG
            {
                B_PROFILE_SCOPE("ImGuiLayer Render");
                m_ImGuiLayer->Begin();
                for (Layer* layer : m_LayerStack)
                    layer->OnImGuiRender();
                m_ImGuiLayer->End();
            }
#endif

#ifdef B_CLIENT
            m_Window->OnUpdate();
#endif
        }
    }

    bool Application::OnWindowClose(WindowCloseEvent& e) {
        B_PROFILE_FUNCTION();
        m_ApplicationState = ApplicationState::ShuttingDown;
        return false;
    }

    bool Application::OnWindowResize(WindowResizeEvent& e) {
        B_PROFILE_FUNCTION();
        if (e.GetWidth() == 0 || e.GetHeight() == 0)
        {
            m_ApplicationState = ApplicationState::Minimized;
            return false;
        }

        m_ApplicationState = ApplicationState::Running;

        Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());

        return false;
    }

    void Application::PushLayer(Layer* layer) {
        B_PROFILE_FUNCTION();
        m_LayerStack.PushLayer(layer);
        layer->OnAttach();
    }

    void Application::PushOverlay(Layer* layer) {
        B_PROFILE_FUNCTION();
        m_LayerStack.PushOverlay(layer);
        layer->OnAttach();
    }
}