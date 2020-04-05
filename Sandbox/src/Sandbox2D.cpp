#include "Sandbox2D.h"
#include <imgui/imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Sandbox2D::Sandbox2D()
    : Layer("Sandbox2D"), m_CameraController(1200.0f / 720.0f, false)
{
}

void Sandbox2D::OnAttach()
{
    B_PROFILE_FUNCTION();
    m_Texture = Bell::Texture2D::Create("assets/textures/bigmisssteak.png");

    Bell::Input::Remap("camera_move_left", Bell::KeyAlternative(Bell::Keys::A));
    Bell::Input::Remap("camera_move_right", Bell::KeyAlternative(Bell::Keys::D));
    Bell::Input::Remap("camera_move_up", Bell::KeyAlternative(Bell::Keys::W));
    Bell::Input::Remap("camera_move_down", Bell::KeyAlternative(Bell::Keys::S));
}

void Sandbox2D::OnDetach()
{
    B_PROFILE_FUNCTION();
}

void Sandbox2D::OnUpdate(Bell::Timestep deltaTime)
{
    B_PROFILE_FUNCTION();

    // Update
    {
        B_PROFILE_SCOPE("CameraController::OnUpdate");
        m_CameraController.OnUpdate(deltaTime);
    }

    // Render
    {
        B_PROFILE_SCOPE("Renderer Prep");
        Bell::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
        Bell::RenderCommand::Clear();
    }

    {
        B_PROFILE_SCOPE("Renderer Draw");
        Bell::Renderer2D::BeginScene(m_CameraController.GetCamera());

        //Bell::Renderer2D::DrawQuad(m_SquarePosition, m_SquareScale, m_Rotation, m_SquareColor);
        Bell::Renderer2D::DrawQuad(m_SquarePosition, m_SquareScale, 0, m_Texture, m_SquareColor, m_TilingFactor);
        Bell::Renderer2D::DrawQuad({ 1,1,1 }, { 1, 1 }, 0, m_SquareColor);

        Bell::Renderer2D::EndScene();
    }
}

void Sandbox2D::OnImGuiRender()
{
    B_PROFILE_FUNCTION();
    ImGui::Begin("Sandbox 2D Settings");

    ImGui::DragFloat2("Square Position", glm::value_ptr(m_SquarePosition), 0.1f);
    ImGui::DragFloat2("Square Scale", glm::value_ptr(m_SquareScale), 0.1f, 0.1f, std::numeric_limits<float>::max());
    ImGui::SliderFloat("Rotation", &m_Rotation, 0.0f, 360.0f);
    ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
    ImGui::SliderFloat("Tiling Factor", &m_TilingFactor, 0.0f, 10.0f);

    ImGui::End();
}

void Sandbox2D::OnEvent(Bell::Event& event)
{
    B_PROFILE_FUNCTION();
    m_CameraController.OnEvent(event);
}
