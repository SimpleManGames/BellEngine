
// __MAIN_FILE__ is only to be defined once in the file that
// defines Bell::CreateApplication
#define __MAIN_FILE__
#include <Bell.h>

#include <Platform/OpenGL/OpenGLShader.h>

#include <imgui/imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Sandbox2D.h"
#include "ServerLayer.h"
#include "ClientLayer.h"

class ExampleLayer : public Bell::Layer
{
public:
    ExampleLayer()
        : Layer("Example"), m_CameraController(1200.0f / 720.0f, false)
    {
        m_VertexArray = Bell::VertexArray::Create();

        float vertices[3 * 7] = {
            -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
             0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
             0.0f,  0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f,
        };
        Bell::Ref<Bell::VertexBuffer> vertexBuffer = Bell::VertexBuffer::Create(vertices, sizeof(vertices));

        Bell::BufferLayout layout = {
            { Bell::ShaderDataType::Float3, "a_Position" },
            { Bell::ShaderDataType::Float4, "a_Color" }
        };

        vertexBuffer->SetLayout(layout);
        m_VertexArray->AddVertexBuffer(vertexBuffer);

        uint32_t indices[3] = { 0, 1, 2 };
        Bell::Ref<Bell::IndexBuffer> indexBuffer = Bell::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));
        m_VertexArray->SetIndexBuffer(indexBuffer);

        float squareVertices[5 * 4] = {
             -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
              0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
              0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
             -0.5f,  0.5f, 0.0f, 0.0f, 1.0f
        };

        m_SquareVA = Bell::VertexArray::Create();

        Bell::Ref<Bell::VertexBuffer> squareVB = Bell::VertexBuffer::Create(squareVertices, sizeof(squareVertices));

        squareVB->SetLayout({
            { Bell::ShaderDataType::Float3, "a_Position" },
            { Bell::ShaderDataType::Float2, "a_TexCoord" },
            });
        m_SquareVA->AddVertexBuffer(squareVB);

        uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
        Bell::Ref<Bell::IndexBuffer> squareIB = Bell::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t));
        m_SquareVA->SetIndexBuffer(squareIB);

        auto vertexColorShader = m_ShaderLibrary.Load("VertexPosColor", "assets/shaders/VertexColor.glsl");
        auto flatColorShader = m_ShaderLibrary.Load("FlatColor", "assets/shaders/FlatColor.glsl");
        auto textureShader = m_ShaderLibrary.Load("assets/shaders/Texture.glsl");

        m_Texture = Bell::Texture2D::Create("assets/textures/bigmisssteak.png");
        m_AlphaImageTest = Bell::Texture2D::Create("assets/textures/sheet.png");

        OpenGLShaderCast(textureShader)->Bind();
        OpenGLShaderCast(textureShader)->UploadUniformInt("u_Texture", 0);
    }

    void OnUpdate(Bell::Timestep deltaTime) override
    {
        // Update
        m_CameraController.OnUpdate(deltaTime);

        // Render
        Bell::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
        Bell::RenderCommand::Clear();

        Bell::Renderer::BeginScene(m_CameraController.GetCamera());

        glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

        auto flatColorShader = m_ShaderLibrary.Get("FlatColor");

        flatColorShader->Bind();
        OpenGLShaderCast(flatColorShader)->UploadUniformFloat4("u_Color", m_SquareColor);

        for (int y = 0; y < m_SquareGridX; y++)
        {
            for (int x = 0; x < m_SquareGridY; x++)
            {
                glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
                glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
                Bell::Renderer::Submit(flatColorShader, m_SquareVA, transform);
            }
        }

        auto textureShader = m_ShaderLibrary.Get("Texture");

        m_Texture->Bind();
        Bell::Renderer::Submit(textureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

        m_AlphaImageTest->Bind();
        Bell::Renderer::Submit(textureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(2.72f, 1.28f, 1.0f)));

        Bell::Renderer::EndScene();
    }

    virtual void OnImGuiRender() override
    {
        ImGui::Begin("Example Layer Settings");

        ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
        ImGui::DragInt("Grid X", &m_SquareGridX, 1.0f, 1, 100);
        ImGui::DragInt("Grid Y", &m_SquareGridY, 1.0f, 1, 100);

        ImGui::End();
    }

    void OnEvent(Bell::Event& event) override {
        m_CameraController.OnEvent(event);
    }

private:
    Bell::ShaderLibrary m_ShaderLibrary;
    Bell::Ref<Bell::VertexArray> m_VertexArray;

    Bell::Ref<Bell::VertexArray> m_SquareVA;

    Bell::Ref<Bell::Texture> m_Texture, m_AlphaImageTest;

    int m_SquareGridX = 20, m_SquareGridY = 20;

    Bell::OrthographicCameraController m_CameraController;

    glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };
};

// Default class for entry point
class Sandbox : public Bell::Application {
public:
    Sandbox()
    {
        //PushLayer(new ExampleLayer());
        PushLayer(new ClientLayer());
    }
    ~Sandbox() { }
};

class SandboxServer : public Bell::Application
{
public:
    SandboxServer()
    {
        PushLayer(new ServerLayer());
    }
    ~SandboxServer() {}
};

// Application side function for defining entry point
Bell::Application* Bell::CreateApplication(Bell::Config config)
{
    if (config.launchType == Bell::LaunchType::Server)
        return new SandboxServer();

    if (config.launchType == Bell::LaunchType::Client)
        return new Sandbox();

#ifdef B_CLIENT
    return new Sandbox();
#endif
#ifdef B_SERVER
    return new SandboxServer();
#endif
}