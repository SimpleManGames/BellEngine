#ifndef _SANDBOX2D_H
#define _SANDBOX2D_H

#include "Bell.h"

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
    
    Bell::Ref<Bell::VertexArray> m_SquareVA;
    Bell::Ref<Bell::Shader> m_FlatColorShader;
    glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };
};

#endif // !_SANDBOX2D_H
