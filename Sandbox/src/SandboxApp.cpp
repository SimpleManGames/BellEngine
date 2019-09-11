#include <Bell.h>

#include "Platform/OpenGL/OpenGLShader.h"
#include <glm/gtc/matrix_transform.hpp>

class ExampleLayer : public Bell::Layer
{
public:
    ExampleLayer()
        : Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition({ 0.0f,0.0f,0.0f })
    {

        m_VertexArray.reset(Bell::VertexArray::Create());

        float vertices[3 * 7] = {
            -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
             0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
             0.0f,  0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f,
        };

        std::shared_ptr<Bell::VertexBuffer> vertexBuffer;
        vertexBuffer.reset(Bell::VertexBuffer::Create(vertices, sizeof(vertices)));

        Bell::BufferLayout layout = {
            { Bell::ShaderDataType::Float3, "a_Position" },
            { Bell::ShaderDataType::Float4, "a_Color" }
        };

        vertexBuffer->SetLayout(layout);
        m_VertexArray->AddVertexBuffer(vertexBuffer);

        uint32_t indices[3] = { 0, 1, 2 };
        std::shared_ptr<Bell::IndexBuffer> indexBuffer;
        indexBuffer.reset(Bell::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
        m_VertexArray->SetIndexBuffer(indexBuffer);

        float squareVertices[3 * 4] = {
             -0.5f, -0.5f, 0.0f,
              0.5f, -0.5f, 0.0f,
              0.5f,  0.5f, 0.0f,
             -0.5f,  0.5f, 0.0f
        };

        m_SquareVA.reset(Bell::VertexArray::Create());

        std::shared_ptr<Bell::VertexBuffer> squareVB;
        squareVB.reset(Bell::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
        squareVB->SetLayout({
            { Bell::ShaderDataType::Float3, "a_Position" },
            });
        m_SquareVA->AddVertexBuffer(squareVB);

        uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
        std::shared_ptr<Bell::IndexBuffer> squareIB;
        squareIB.reset(Bell::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
        m_SquareVA->SetIndexBuffer(squareIB);

        std::string vertexSrc = R"(
            #version 330 core

            layout(location = 0) in vec3 a_Position;
            layout(location = 1) in vec4 a_Color;

            uniform mat4 u_ViewProjection;
            uniform mat4 u_Transform;

            out vec3 v_Position;
            out vec4 v_Color;

            void main()
            {
                v_Position = a_Position;
                v_Color = a_Color;
                gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
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

        m_Shader.reset(Bell::Shader::Create(vertexSrc, fragmentSrc));

        std::string flatColorVertexSrc = R"(
            #version 330 core

            layout(location = 0) in vec3 a_Position;

            uniform mat4 u_ViewProjection;
            uniform mat4 u_Transform;

            out vec3 v_Position;
            out vec4 v_Color;

            void main()
            {
                v_Position = a_Position;
                gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
            }
        )";

        std::string flatColorFragmentSrc = R"(
            #version 330 core
            layout(location = 0) out vec4 color;

            in vec3 v_Position;

            uniform vec4 u_Color;

            void main()
            {
                color = u_Color;
            }
        )";

        m_FlatColorShader.reset(Bell::Shader::Create(flatColorVertexSrc, flatColorFragmentSrc));
    }

    void OnUpdate(Bell::Timestep timestep) override
    {
        // Camera
        if (Bell::Input::IsKeyPressed(B_KEY_LEFT))
            m_CameraPosition.x -= m_CameraMoveSpeed * timestep;
        else if (Bell::Input::IsKeyPressed(B_KEY_RIGHT))
            m_CameraPosition.x += m_CameraMoveSpeed * timestep;

        if (Bell::Input::IsKeyPressed(B_KEY_UP))
            m_CameraPosition.y += m_CameraMoveSpeed * timestep;
        else if (Bell::Input::IsKeyPressed(B_KEY_DOWN))
            m_CameraPosition.y -= m_CameraMoveSpeed * timestep;

        if (Bell::Input::IsKeyPressed(B_KEY_A))
            m_CameraRotation += m_CameraRotationSpeed * timestep;
        if (Bell::Input::IsKeyPressed(B_KEY_D))
            m_CameraRotation -= m_CameraRotationSpeed * timestep;

        Bell::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
        Bell::RenderCommand::Clear();

        m_Camera.SetPosition(m_CameraPosition);
        m_Camera.SetRotation(m_CameraRotation);

        Bell::Renderer::BeginScene(m_Camera);

        glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

        glm::vec4 redColor(0.8f, 0.3f, 0.2f, 1.0f);
        glm::vec4 blueColor(0.2f, 0.3f, 0.8f, 1.0f);
        for (int y = 0; y < 20; y++)
        {
            for (int x = 0; x < 20; x++)
            {
                glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
                glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
                if (x % 2 == 0)
                    OpenGLShaderCast(m_FlatColorShader)->UploadUniformFloat4("u_Color", redColor);
                else
                    OpenGLShaderCast(m_FlatColorShader)->UploadUniformFloat4("u_Color", blueColor);

                Bell::Renderer::Submit(m_FlatColorShader, m_SquareVA, transform);
            }
        }

        Bell::Renderer::Submit(m_Shader, m_VertexArray);

        Bell::Renderer::EndScene();
    }

    void OnEvent(Bell::Event& event) override { }

private:
    std::shared_ptr<Bell::Shader> m_Shader;
    std::shared_ptr <Bell::VertexArray> m_VertexArray;

    std::shared_ptr<Bell::Shader> m_FlatColorShader;
    std::shared_ptr<Bell::VertexArray> m_SquareVA;

    Bell::OrthographicCamera m_Camera;
    glm::vec3 m_CameraPosition;
    float m_CameraMoveSpeed = 5.0f;

    float m_CameraRotation = 0.0f;
    float m_CameraRotationSpeed = 45.0f;
};

// Default class for entry point
class Sandbox : public Bell::Application {
public:
    Sandbox()
    {
        PushLayer(new ExampleLayer());
    }
    ~Sandbox() { }
};

// Application side function for defining entry point
Bell::Application* Bell::CreateApplication()
{
    return new Sandbox();
}