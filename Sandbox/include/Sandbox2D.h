#ifndef _SANDBOX2D_H
#define _SANDBOX2D_H

#include <Bell.h>
#include "entt/entt.hpp"

class Sandbox2D : public Bell::Layer
{
public:
    Sandbox2D();
    virtual ~Sandbox2D() = default;

    virtual void OnAttach();
    virtual void OnDetach();

    void OnUpdate(Bell::Timestep deltaTime) override;
    virtual void OnImGuiRender() override;
    void OnEvent(Bell::Event& event) override;

private:
    Bell::OrthographicCameraController m_CameraController;

    Bell::Ref<Bell::Texture2D> m_Texture;
    Bell::Ref<Bell::VertexArray> m_SquareVA;
    Bell::Ref<Bell::Shader> m_FlatColorShader;
    glm::vec3 m_SquarePosition = { 1.0f, 1.0f, 1.0f };
    glm::vec2 m_SquareScale = { 1, 1 };
    glm::vec4 m_SquareColor = { 1.0f, 0.8f, 0.8f, 1.0f };
    float m_Rotation = 0.0f;
    float m_TilingFactor = 1.0f;

    //Bell::ParticleSystem m_ParticleSystem;
    //Bell::ParticleProperties m_Particles;

    Bell::Ref<Bell::Texture2D> m_SpriteSheet;
    Bell::Ref<Bell::SubTexture2D> m_SubTexture, m_TreeSubTexture;

    Bell::Ref<Bell::FrameBuffer> m_FrameBuffer;

    // Stress test
    glm::vec2 m_GridSize = { 1, 1 };
    Bell::Ref<Bell::Texture2D> m_TextureSlotTest[32];
};

#endif // !_SANDBOX2D_H