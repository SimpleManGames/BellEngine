#ifndef RENDERERSTATSPANEL_H
#define RENDERERSTATSPANEL_H

#include <Bell.h>
#include <imgui.h>

namespace Bell
{
    class RendererStatsPanel
    {
    public:
        RendererStatsPanel() = default;

        void OnImGuiRender();

        bool GetVisiblity();
        void SetVisiblity(bool visiblity);

    private:
        bool m_IsOpened = false;
    };
} // namespace Bell

#endif // RENDERERSTATSPANEL_H