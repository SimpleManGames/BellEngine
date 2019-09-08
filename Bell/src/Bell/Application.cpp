#include "bpch.h"
#include "Application.h"

#include "Bell/Log.h"

#include <glad/glad.h>

#include "Input.h"

namespace Bell {
    Application* Application::s_Instance = nullptr;

    static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
    {
        switch (type)
        {
        case Bell::ShaderDataType::Float:  return GL_FLOAT;
        case Bell::ShaderDataType::Float2: return GL_FLOAT;
        case Bell::ShaderDataType::Float3: return GL_FLOAT;
        case Bell::ShaderDataType::Float4: return GL_FLOAT;
        case Bell::ShaderDataType::Mat3:   return GL_FLOAT;
        case Bell::ShaderDataType::Mat4:   return GL_FLOAT;
        case Bell::ShaderDataType::Int:    return GL_INT;
        case Bell::ShaderDataType::Int2:   return GL_INT;
        case Bell::ShaderDataType::Int3:   return GL_INT;
        case Bell::ShaderDataType::Int4:   return GL_INT;
        case Bell::ShaderDataType::Bool:   return GL_BOOL;
        }

        B_CORE_ASSERT(false, "Unknown ShaderDataType");
        return 0;
    }

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

        float vertices[3 * 7] = {
            -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
             0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
             0.0f,  0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f,
        };

        m_VertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));
        
        {
            BufferLayout layout = {
                { ShaderDataType::Float3, "a_Position" },
                { ShaderDataType::Float4, "a_Color" },

            };

            m_VertexBuffer->SetLayout(layout);
        }

        uint32_t index = 0;
        const auto& layout = m_VertexBuffer->GetLayout();
        for (const auto& element : layout)
        {
            glEnableVertexAttribArray(index);
            glVertexAttribPointer(index, 
                element.GetComponentCount(), 
                ShaderDataTypeToOpenGLBaseType(element.Type), 
                element.Normalized ? GL_TRUE : GL_FALSE, 
                layout.GetStride(),
                (const void*)element.Offset);
            index++;
        }


        uint32_t indices[3] = { 0, 1, 2 };
        m_IndexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));

        std::string vertexSrc = R"(
            #version 330 core

            layout(location = 0) in vec3 a_Position;
            layout(location = 1) in vec4 a_Color;

            out vec3 v_Position;
            out vec4 v_Color;

            void main()
            {
                v_Position = a_Position;
                v_Color = a_Color;
                gl_Position = vec4(a_Position, 1.0);
            }
        )";

        std::string fragmentSrc = R"(
            #version 330 core
            layout(location = 0) out vec4 color;

            in vec3 v_Position;
            in vec4 v_Color;

            void main()
            {
                color = vec4(v_Position * 0.5 + 0.5, 1.0);
                color = v_Color;
            }
        )";

        m_Shader.reset(Shader::Create(vertexSrc, fragmentSrc));
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

            m_Shader->Bind();
            glBindVertexArray(m_VertexArray);
            glDrawElements(GL_TRIANGLES, m_IndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);

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

    bool Application::OnWindowClose(WindowCloseEvent& e)
    {
        m_Running = false;
        return false;
    }

    void Application::PushLayer(Layer* layer)
    {
        m_LayerStack.PushLayer(layer);
        layer->OnAttach();
    }

    void Application::PushOverlay(Layer* layer)
    {
        m_LayerStack.PushOverlay(layer);
        layer->OnAttach();
    }
}