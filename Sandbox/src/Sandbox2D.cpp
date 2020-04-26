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

    for (int i = 0; i < 31; i++)
    {
        m_TextureSlotTest[i] = Bell::Texture2D::Create(1, 1);
        uint32_t randomHex = 0xffffffff * (i + 1);
        m_TextureSlotTest[i]->SetData(&randomHex, sizeof(uint32_t));
    }

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
    Bell::Renderer2D::ResetStats();
    Bell::Renderer2D::StatsBeginFrame();

    {
        B_PROFILE_SCOPE("Renderer Prep");
        Bell::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
        Bell::RenderCommand::Clear();
    }

    {
        B_PROFILE_SCOPE("Renderer Draw");
        Bell::Renderer2D::BeginScene(m_CameraController.GetCamera());

        //Bell::Renderer2D::DrawQuad(m_SquarePosition, m_SquareScale, m_Rotation, m_SquareColor);
        Bell::Renderer2D::DrawQuad(m_SquarePosition, m_SquareScale, m_Rotation, m_Texture, m_SquareColor, m_TilingFactor);

        //Bell::Renderer2D::EndScene();
        //
        //Bell::Renderer2D::BeginScene(m_CameraController.GetCamera());
        {
            B_PROFILE_SCOPE("Grid Stress Test");
            for (int x = 0; x < m_GridSize.x; x++)
            {
                for (int y = 0; y < m_GridSize.y; y++)
                {
                    glm::vec4 color = { x / m_GridSize.x, 0.4f, y / m_GridSize.y, 0.8f };
                    Bell::Renderer2D::DrawQuad({ x, y, 1 }, { 1.0, 1.0 }, 0, m_TextureSlotTest[(x + y) % 31]);
                }
            }
        }
        Bell::Renderer2D::EndScene();
        Bell::Renderer2D::StatsEndFrame();
    }
}

void Sandbox2D::OnImGuiRender()
{
    B_PROFILE_FUNCTION();
    ImGui::Begin("Sandbox 2D Settings");

    ImGui::DragFloat3("Square Position", glm::value_ptr(m_SquarePosition), 0.1f);
    ImGui::DragFloat2("Square Scale", glm::value_ptr(m_SquareScale), 0.1f, 0.1f, std::numeric_limits<float>::max());
    ImGui::SliderFloat("Rotation", &m_Rotation, 0.0f, 360.0f);
    ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
    ImGui::SliderFloat("Tiling Factor", &m_TilingFactor, 0.0f, 10.0f);

    ImGui::DragFloat2("Grid Size", glm::value_ptr(m_GridSize), 1.0f);

    auto stats = Bell::Renderer2D::GetStats();
    ImGui::Text("Renderer2D Stats:");
    ImGui::Text("Draw Calls: %d", stats.DrawCalls);
    ImGui::Text("Quad Count: %d", stats.QuadCount);
    ImGui::Text("Texture Slots Used: %d", stats.UsedTextureSlots);
    ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
    ImGui::Text("Indices: %d", stats.GetTotalIndexCount());

    ImGui::Text("Frame Info!");
    ImGui::Text("Frame count: %d", stats.FrameCount);

    float averageRenderTime = stats.TotalFrameRenderTime / stats.FrameRenderTime.size();
    float averageFPS = 1.0f / averageRenderTime;
    ImGui::Text("Average frame render time: %8.5f (%5.0f fps)", averageRenderTime, averageFPS);

    ImGui::End();
}

void Sandbox2D::OnEvent(Bell::Event& event)
{
    B_PROFILE_FUNCTION();
    m_CameraController.OnEvent(event);
}
