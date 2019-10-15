#include "Sandbox2D.h"
#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Platform/OpenGL/OpenGLShader.h"

Sandbox2D::Sandbox2D()
    : Layer("Sandbox2D"), m_CameraController(1200.0f / 720.0f, false)
{
}

void Sandbox2D::OnAttach()
{
    float squareVertices[5 * 4] = {
         -0.5f, -0.5f, 0.0f,
          0.5f, -0.5f, 0.0f,
          0.5f,  0.5f, 0.0f,
         -0.5f,  0.5f, 0.0f
    };

    m_SquareVA = Bell::VertexArray::Create();

    Bell::Ref<Bell::VertexBuffer> squareVB = Bell::VertexBuffer::Create(squareVertices, sizeof(squareVertices));
    squareVB->SetLayout({
        { Bell::ShaderDataType::Float3, "a_Position" },
        });
    m_SquareVA->AddVertexBuffer(squareVB);

    uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
    Bell::Ref<Bell::IndexBuffer> squareIB = Bell::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t));
    m_SquareVA->SetIndexBuffer(squareIB);

    m_FlatColorShader = Bell::Shader::Create("assets/shaders/FlatColor.glsl");
}

void Sandbox2D::OnDetach()
{
}

void Sandbox2D::OnUpdate(Bell::Timestep deltaTime)
{
    // Update
    m_CameraController.OnUpdate(deltaTime);

    // Render
    Bell::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
    Bell::RenderCommand::Clear();

    Bell::Renderer::BeginScene(m_CameraController.GetCamera());

    OpenGLShaderCast(m_FlatColorShader)->Bind();
    OpenGLShaderCast(m_FlatColorShader)->UploadUniformFloat4("u_Color", m_SquareColor);

    Bell::Renderer::Submit(m_FlatColorShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

    Bell::Renderer::EndScene();
}

void Sandbox2D::OnImGuiRender()
{
    ImGui::Begin("Sandbox 2D Settings");

    ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));

    ImGui::End();
}

void Sandbox2D::OnEvent(Bell::Event& event)
{
    m_CameraController.OnEvent(event);
}
