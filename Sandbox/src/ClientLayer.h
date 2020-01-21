#ifndef _CLIENT_LAYER_H
#define _CLIENT_LAYER_H

#include <Bell.h>
#include <Bell/Networking/Client/Client.h>

class ClientLayer : public Bell::Layer
{
    friend class Bell::Client;

public:
    ClientLayer();
    virtual ~ClientLayer() = default;

    virtual void OnAttach();
    virtual void OnDetach();

    void OnUpdate(Bell::Timestep deltaTime) override;
    void OnEvent(Bell::Event& e) override;
    void OnImGuiRender() override;

    void OnPlayerJoin(Bell::Packet& packet);
    void OnPlayerLeave(Bell::Packet& packet);
    void OnSnapshot(Bell::Packet& packet);

    void OnSpawnPoint(Bell::Packet& packet);

    void SendPlayerPosition(const glm::vec3& position);
private:
    Bell::Client m_Client;

    Bell::OrthographicCameraController m_CameraController;
    Bell::Ref<Bell::Texture2D> m_Texture;
    glm::vec2 m_SquarePosition = { 1, 1 };
    glm::vec2 m_SquareScale = { 1, 1 };
    glm::vec4 m_SquareColor = { 1.0f, 0.8f, 0.8f, 1.0f };
    float m_Rotation = 0.0f;
    float m_TextureScale = 1.0f;
};

#endif // !_CLIENT_LAYER_H