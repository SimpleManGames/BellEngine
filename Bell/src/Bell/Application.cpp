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

        m_ImGuiLayer = new ImGuiLayer();
        PushOverlay(m_ImGuiLayer);

        glGenVertexArrays(1, &m_VertexArray);
        glBindVertexArray(m_VertexArray);

        glGenBuffers(1, &m_VertexBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);

        float vertices[3 * 3] = {
            -0.5f, -0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            0.0f, 0.5f, 0.0f
        };

        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

        glGenBuffers(1, &m_IndexBuffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBuffer);

        unsigned int indices[3] = { 0, 1, 2 };
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    }

    Application::~Application() { }

    void Application::OnEvent(Event& e)
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
            glClearColor(0.1f, 0.1f, 0.1f, 1);
            glClear(GL_COLOR_BUFFER_BIT);

            glBindVertexArray(m_VertexArray);
            glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);

            // Update each layer
            for (Layer* layer : m_LayerStack)
                layer->OnUpdate();

            m_ImGuiLayer->Begin();
            for (Layer* layer : m_LayerStack)
                layer->OnImGuiRender();
            m_ImGuiLayer->End();

            m_Window->OnUpdate();
        }
    }

    bool Application::OnWindowClose(WindowCloseEvent & e)
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