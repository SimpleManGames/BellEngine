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

    Bell::Renderer2D::BeginScene(m_CameraController.GetCamera());

    Bell::Renderer2D::DrawQuad({ 0,0 }, { 1,1 }, m_SquareColor);

    Bell::Renderer2D::EndScene();

    // TODO: Add these func - Shader::SetMat4, Shader::SetFloat4
    //OpenGLShaderCast(m_FlatColorShader)->Bind();
    //OpenGLShaderCast(m_FlatColorShader)->UploadUniformFloat4("u_Color", m_SquareColor);
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
