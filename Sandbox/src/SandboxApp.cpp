#include <Bell.h>

#include "Platform/OpenGL/OpenGLShader.h"

#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

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

        Bell::Ref<Bell::VertexBuffer> vertexBuffer;
        vertexBuffer.reset(Bell::VertexBuffer::Create(vertices, sizeof(vertices)));

        Bell::BufferLayout layout = {
            { Bell::ShaderDataType::Float3, "a_Position" },
            { Bell::ShaderDataType::Float4, "a_Color" }
        };

        vertexBuffer->SetLayout(layout);
        m_VertexArray->AddVertexBuffer(vertexBuffer);

        uint32_t indices[3] = { 0, 1, 2 };
        Bell::Ref<Bell::IndexBuffer> indexBuffer;
        indexBuffer.reset(Bell::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
        m_VertexArray->SetIndexBuffer(indexBuffer);

        float squareVertices[5 * 4] = {
             -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
              0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
              0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
             -0.5f,  0.5f, 0.0f, 0.0f, 1.0f
        };

        m_SquareVA.reset(Bell::VertexArray::Create());

        std::shared_ptr<Bell::VertexBuffer> squareVB;
        squareVB.reset(Bell::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
        squareVB->SetLayout({
            { Bell::ShaderDataType::Float3, "a_Position" },
            { Bell::ShaderDataType::Float2, "a_TexCoord" },
            });
        m_SquareVA->AddVertexBuffer(squareVB);

        uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
        std::shared_ptr<Bell::IndexBuffer> squareIB;
        squareIB.reset(Bell::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
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
        // Camera
        if (Bell::Input::IsKeyPressed(B_KEY_LEFT))
            m_CameraPosition.x -= m_CameraMoveSpeed * deltaTime;
        else if (Bell::Input::IsKeyPressed(B_KEY_RIGHT))
            m_CameraPosition.x += m_CameraMoveSpeed * deltaTime;

        if (Bell::Input::IsKeyPressed(B_KEY_UP))
            m_CameraPosition.y += m_CameraMoveSpeed * deltaTime;
        else if (Bell::Input::IsKeyPressed(B_KEY_DOWN))
            m_CameraPosition.y -= m_CameraMoveSpeed * deltaTime;

        if (Bell::Input::IsKeyPressed(B_KEY_A))
            m_CameraRotation += m_CameraRotationSpeed * deltaTime;
        if (Bell::Input::IsKeyPressed(B_KEY_D))
            m_CameraRotation -= m_CameraRotationSpeed * deltaTime;

        Bell::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
        Bell::RenderCommand::Clear();

        m_Camera.SetPosition(m_CameraPosition);
        m_Camera.SetRotation(m_CameraRotation);

        Bell::Renderer::BeginScene(m_Camera);

        glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

        auto flatColorShader = m_ShaderLibrary.Get("FlatColor");

        flatColorShader->Bind();
        OpenGLShaderCast(flatColorShader)->UploadUniformFloat4("u_Color", m_SquareColor);

        for (int y = 0; y < 20; y++)
        {
            for (int x = 0; x < 20; x++)
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
        ImGui::Begin("Settings");

        ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));

        ImGui::End();
    }

    void OnEvent(Bell::Event& event) override { }

private:
    Bell::ShaderLibrary m_ShaderLibrary;
    Bell::Ref<Bell::VertexArray> m_VertexArray;

    Bell::Ref<Bell::VertexArray> m_SquareVA;

    Bell::Ref<Bell::Texture> m_Texture, m_AlphaImageTest;

    Bell::OrthographicCamera m_Camera;
    glm::vec3 m_CameraPosition;
    float m_CameraMoveSpeed = 5.0f;

    float m_CameraRotation = 0.0f;
    float m_CameraRotationSpeed = 45.0f;

    glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };
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