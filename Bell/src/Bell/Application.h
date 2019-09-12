// Application Definition
// ----------------------

#ifndef APPLICATION_H
#define APPLICATION_H

#include "Core.h"
#include "Window.h"
#include "Events/Event.h"
#include "Bell/Layer/LayerStack.h"
#include "Events/ApplicationEvent.h"

#include "Bell/Core/Timestep.h"

#include "Bell/ImGui/ImGuiLayer.h"

namespace Bell
{
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
    private:
        bool OnWindowClose(WindowCloseEvent& e);

    private:
        Scope<Window> m_Window;
        ImGuiLayer* m_ImGuiLayer;
        bool m_Running = true;
        LayerStack m_LayerStack;
        float m_LastFrameTime = 0.0f;

    private:
        static Application* s_Instance;
    };

    // To be defined in client
    Application* CreateApplication();
}

#endif // !APPLICATION_H