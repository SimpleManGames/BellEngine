#ifndef _EDITORLAYER_H
#define _EDITORLAYER_H

#include <Bell.h>
#include "SceneHierarchyPanel.h"
#include "RendererStatsPanel.h"

namespace Bell::Editor
{
    class EditorLayer : public Layer
    {
    public:
        EditorLayer();
        virtual ~EditorLayer() = default;

        virtual void OnAttach();
        virtual void OnDetach();

        void OnUpdate(Timestep deltaTime) override;
        virtual void OnImGuiRender() override;
        void OnEvent(Event &event) override;

    private:
        OrthographicCameraController m_CameraController;
        Ref<Scene> m_ActiveScene;
        Entity m_CameraEntity;

        // Test
        Entity m_Square;

        Ref<FrameBuffer> m_FrameBuffer;

        glm::vec2 m_ViewportSize = {0, 0};
        bool m_ViewportFocused = false , m_ViewportHovered = false;

        SceneHierarchyPanel m_HierarchyPanel;
        RendererStatsPanel m_RendererStatsPanel;
    };
} // namespace Bell::Editor
#endif // !_EDITORLAYER_H