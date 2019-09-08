// Application Definition
// ----------------------

#ifndef APPLICATION_H
#define APPLICATION_H

#include "Core.h"
#include "Window.h"
#include "Events/Event.h"
#include "Bell/Layer/LayerStack.h"
#include "Events/ApplicationEvent.h"

#include "Bell/ImGui/ImGuiLayer.h"

#include "Bell/Renderer/Shader.h"
#include "Bell/Renderer/Buffer.h"
#include "Bell/Renderer/VertexArray.h"

namespace Bell
{
    class BELL_API Application
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

        std::unique_ptr<Window> m_Window;
        ImGuiLayer* m_ImGuiLayer;
        bool m_Running = true;
        LayerStack m_LayerStack;

        std::shared_ptr<Shader> m_Shader;
        std::shared_ptr <VertexArray> m_VertexArray;
               
        std::shared_ptr<Shader> m_BlueShader;
        std::shared_ptr <VertexArray> m_SquareVA;

    private:
        static Application* s_Instance;
    };

    // To be defined in client
    Application* CreateApplication();
}

#endif // !APPLICATION_H