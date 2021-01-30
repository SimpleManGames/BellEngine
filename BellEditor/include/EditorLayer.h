#ifndef _EDITORLAYER_H
#define _EDITORLAYER_H

#include <Bell.h>

namespace Bell
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
        Entity m_Square;

        Ref<Texture2D> m_Texture;
        Ref<VertexArray> m_SquareVA;
        Ref<Shader> m_FlatColorShader;
        glm::vec3 m_SquarePosition = {1.0f, 1.0f, 1.0f};
        glm::vec2 m_SquareScale = {1, 1};
        glm::vec4 m_SquareColor = {1.0f, 0.8f, 0.8f, 1.0f};
        float m_Rotation = 0.0f;
        float m_TilingFactor = 1.0f;

        Ref<Texture2D> m_SpriteSheet;
        Ref<SubTexture2D> m_SubTexture, m_TreeSubTexture;

        Ref<FrameBuffer> m_FrameBuffer;

        glm::vec2 m_ViewportSize = {0, 0};
        bool m_ViewportFocused = false , m_ViewportHovered = false;

        // Stress test
        glm::vec2 m_GridSize = {1, 1};
        Ref<Texture2D> m_TextureSlotTest[32];
    };
} // namespace Bell
#endif // !_EDITORLAYER_H