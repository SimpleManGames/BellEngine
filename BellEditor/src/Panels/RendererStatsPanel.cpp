#include "RendererStatsPanel.h"

namespace Bell
{
    void RendererStatsPanel::OnImGuiRender()
    {
        if(!m_IsOpened)
        {
            return;
        }

        ImGui::Begin("Renderer Info");

        auto stats = Renderer2D::GetStats();
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

        ImGui::End(); // Renderer Info
    }

    bool RendererStatsPanel::GetVisiblity()
    {
        return m_IsOpened;
    }
    void RendererStatsPanel::SetVisiblity(bool visible)
    {
        m_IsOpened = visible;
    }
} // namespace Bell
