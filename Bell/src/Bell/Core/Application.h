// Application Definition
// ----------------------

#ifndef _APPLICATION_H
#define _APPLICATION_H

#include "Core.h"
#include "Window.h"
#include "Events/Event.h"
#include "Bell/Layer/LayerStack.h"
#include "Events/ApplicationEvent.h"

#include "Bell/Core/Timestep.h"

#include "Bell/ImGui/ImGuiLayer.h"

namespace Bell
{
    enum class ApplicationState
    {
        Invalid,
        Constructing,
        Initialiing,
        Running,
        Minimized,
        ShuttingDown,
        Destroying
    };

    class Application
    {
    public:
        Application();
        virtual ~Application();

        // Run loop using m_Running
        void Run();

        // Function used for window event callbacks
        // Handles event dispatching
        void OnEvent(Event& e);

        void PushLayer(Layer* layer);
        void PushOverlay(Layer* layer);

        inline static Application& Get() { return *s_Instance; }
        inline Window& GetWindow() { return *m_Window; }

        inline ApplicationState GetApplicationState() { return m_ApplicationState; }
    private:
        bool OnWindowClose(WindowCloseEvent& e);
        bool OnWindowResize(WindowResizeEvent& e);

    private:
        ApplicationState m_ApplicationState = ApplicationState::Invalid;

        Scope<Window> m_Window;
        ImGuiLayer* m_ImGuiLayer;
        LayerStack m_LayerStack;
        float m_LastFrameTime = 0.0f;

    private:
        static Application* s_Instance;
    };

    // To be defined in client
    Application* CreateApplication();
}

#endif // !_APPLICATION_H