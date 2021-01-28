#include "EditorLayer.h"
#include <imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Bell
{
    EditorLayer::EditorLayer()
        : Layer("EditorLayer"), m_CameraController(1200.0f / 720.0f, false)
    {
    }

    void EditorLayer::OnAttach()
    {
        B_PROFILE_FUNCTION();
        m_Texture = Bell::Texture2D::Create("assets/textures/bigmisssteak.png");
        m_SpriteSheet = Bell::Texture2D::Create("assets/textures/sheet.png");

        m_SubTexture = Bell::SubTexture2D::CreateFromCoords(m_SpriteSheet, {8, 3}, {16, 16});
        m_TreeSubTexture = Bell::SubTexture2D::CreateFromCoords(m_SpriteSheet, {2, 0}, {16, 16}, {5, 8});

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

        Bell::FrameBufferSpecification fbSpec;
        fbSpec.Width = 1080; //Bell::Application::Get().GetWindow().GetWidth();
        fbSpec.Height = 720; //Bell::Application::Get().GetWindow().GetHeight();
        m_FrameBuffer = Bell::FrameBuffer::Create(fbSpec);

        m_CameraController.SetZoomLevel(5.0f);
    }

    void EditorLayer::OnDetach()
    {
        B_PROFILE_FUNCTION();
    }

    void EditorLayer::OnUpdate(Bell::Timestep deltaTime)
    {
        B_PROFILE_FUNCTION();

        // Update
        {
            if (m_ViewportFocused)
            {
                B_PROFILE_SCOPE("CameraController::OnUpdate");
                m_CameraController.OnUpdate(deltaTime);
            }
        }

        // Render
        Bell::Renderer2D::ResetStats();
        Bell::Renderer2D::StatsBeginFrame();

        {
            B_PROFILE_SCOPE("Renderer Prep");
            m_FrameBuffer->Bind();

            Bell::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1});
            Bell::RenderCommand::Clear();
        }

        {
            B_PROFILE_SCOPE("Renderer Draw");
            Bell::Renderer2D::BeginScene(m_CameraController.GetCamera());

            Bell::Renderer2D::DrawQuad(m_SquarePosition, m_SquareScale, glm::radians(m_Rotation), m_Texture, m_SquareColor, m_TilingFactor);

            {
                B_PROFILE_SCOPE("Grid Stress Test");
                for (int x = 0; x < m_GridSize.x; x++)
                {
                    for (int y = 0; y < m_GridSize.y; y++)
                    {
                        glm::vec4 color = {x / m_GridSize.x, 0.4f, y / m_GridSize.y, 0.8f};
                        Bell::Renderer2D::DrawQuad({x, y, 1}, {1.0, 1.0}, 0, m_TextureSlotTest[(x + y) % 31]);
                    }
                }
            }

            Bell::Renderer2D::EndScene();
            Bell::Renderer2D::StatsEndFrame();
        }

        Bell::Renderer2D::BeginScene(m_CameraController.GetCamera());
        Bell::Renderer2D::DrawQuad({2, 0, 0}, {1, 1}, 0, m_SubTexture);
        Bell::Renderer2D::DrawQuad({0, 0, 0}, {5, 9}, 0, m_TreeSubTexture);
        Bell::Renderer2D::EndScene();
        m_FrameBuffer->Unbind();
    }

    void EditorLayer::OnImGuiRender()
    {
        B_PROFILE_FUNCTION();

        // Note: Switch this to true to enable dockspace
        static bool dockspaceOpen = true;
        static bool opt_fullscreen_persistant = true;
        bool opt_fullscreen = opt_fullscreen_persistant;
        static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

        // We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
        // because it would be confusing to have two docking targets within each others.
        ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
        if (opt_fullscreen)
        {
            ImGuiViewport *viewport = ImGui::GetMainViewport();
            ImGui::SetNextWindowPos(viewport->Pos);
            ImGui::SetNextWindowSize(viewport->Size);
            ImGui::SetNextWindowViewport(viewport->ID);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
            window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
            window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
        }

        // When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background and handle the pass-thru hole, so we ask Begin() to not render a background.
        if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
            window_flags |= ImGuiWindowFlags_NoBackground;

        // Important: note that we proceed even if Begin() returns false (aka window is collapsed).
        // This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
        // all active windows docked into it will lose their parent and become undocked.
        // We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
        // any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
        ImGui::Begin("DockSpace", &dockspaceOpen, window_flags);
        ImGui::PopStyleVar();

        if (opt_fullscreen)
            ImGui::PopStyleVar(2);

        // DockSpace
        ImGuiIO &io = ImGui::GetIO();
        if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
        {
            ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
            ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
        }

        if (ImGui::BeginMenuBar())
        {
            if (ImGui::BeginMenu("File"))
            {
                // Disabling fullscreen would allow the window to be moved to the front of other windows,
                // which we can't undo at the moment without finer window depth/z control.
                //ImGui::MenuItem("Fullscreen", NULL, &opt_fullscreen_persistant);

                if (ImGui::MenuItem("Exit"))
                    Bell::Application::Get().Close();
                ImGui::EndMenu();
            }

            ImGui::EndMenuBar();
        }

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

        ImGui::Text("Graphics Card Info");
        ImGui::Text("Total Memory Available In KB: %d", stats.TotalMemoryInKB);
        ImGui::Text("Current Memory Available In KB: %d", stats.CurrentAvailableMemoryInKB);

        float averageRenderTime = stats.TotalFrameRenderTime / stats.FrameRenderTime.size();
        float averageFPS = 1.0f / averageRenderTime;
        ImGui::Text("Average frame render time: %8.5f (%5.0f fps)", averageRenderTime, averageFPS);

        ImGui::End(); // Sandbox 2D Settings

        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{0, 0});
        ImGui::Begin("Viewport");

        // Check to see if this ImGui scope is focused/hovered
        m_ViewportFocused = ImGui::IsWindowFocused();
        m_ViewportHovered = ImGui::IsWindowHovered();
        // Block events so that we aren't affect them on ImGui windows and in the scene view
        Application::Get().GetImGuiLayer()->BlockEvents(!m_ViewportFocused || !m_ViewportHovered);

        // Getting the size of this ImGui scope to adjust our frame buffer that we render here
        ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
        // Check to see if last frame's viewport was a different size
        if (m_ViewportSize != *((glm::vec2 *)&viewportPanelSize))
        {
            // Attempt to resize the buffer and set relevant variables
            if (m_FrameBuffer->Resize((uint32_t)viewportPanelSize.x, (uint32_t)viewportPanelSize.y))
            {
                m_ViewportSize = {viewportPanelSize.x, viewportPanelSize.y};
                m_CameraController.OnResize(viewportPanelSize.x, viewportPanelSize.y);
            }
        }

        uint32_t textureID = m_FrameBuffer->GetColorAttachmentRendererID();
        ImGui::Image((void *)((size_t)textureID), ImVec2{m_ViewportSize.x, m_ViewportSize.y}, ImVec2{0, 1}, ImVec2{1, 0});

        ImGui::End(); // Viewport
        ImGui::PopStyleVar();

        ImGui::End(); // DockSpace
    }

    void EditorLayer::OnEvent(Bell::Event &event)
    {
        B_PROFILE_FUNCTION();

        if (event.Handled)
            return;

        m_CameraController.OnEvent(event);
    }
} // namespace Bell