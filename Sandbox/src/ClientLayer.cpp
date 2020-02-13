#include "ClientLayer.h"
#include <imgui/imgui.h>
#include <glm/gtc/type_ptr.hpp>

#include "Bell/Networking/Network.h"
#include "Bell/Networking/NetworkHost.h"
#include "Bell/Networking/NetworkConstants.h"

#include "Bell/Networking/Packet/Packet.h"
#include "Bell/Networking/Packet/PacketFuncHandler.h"

ClientLayer::ClientLayer(const std::string ip)
    : Layer("Client Layer"), m_CameraController(1200.0f / 720.0f, false)
{
    B_PACKET_FUNCTION_DEF(Bell::ClientCommand::PlayerJoin, ClientLayer::OnPlayerJoin);
    B_PACKET_FUNCTION_DEF(Bell::ClientCommand::PlayerLeave, ClientLayer::OnPlayerLeave);
    B_PACKET_FUNCTION_DEF(Bell::ClientCommand::Snapshot, ClientLayer::OnSnapshot);

    B_PACKET_FUNCTION_DEF(Bell::ClientCommand::SpawnPoint, ClientLayer::OnSpawnPoint);

    auto peer = m_Client.CreateAsClient(ip);
    m_Client.m_ServerPeer = *peer;
    m_Client.m_Player = &m_Client.m_Entities[m_Client.GetPeerID()];
}

void ClientLayer::OnAttach()
{
    m_Texture = Bell::Texture2D::Create("../assets/textures/bigmisssteak.png");
}

void ClientLayer::OnDetach()
{
    m_Client.DisconnectFromPeer(m_Client.m_ServerPeer);
}

void ClientLayer::OnUpdate(Bell::Timestep deltaTime)
{
    m_Client.Tick();

    //m_CameraController.OnUpdate(deltaTime);

    m_SquarePosition.y += Bell::Input::IsKeyPressed((int)Bell::Key::W) * deltaTime * 1.0f;
    m_SquarePosition.y -= Bell::Input::IsKeyPressed((int)Bell::Key::S) * deltaTime * 1.0f;

    m_SquarePosition.x += Bell::Input::IsKeyPressed((int)Bell::Key::D) * deltaTime * 1.0f;
    m_SquarePosition.x -= Bell::Input::IsKeyPressed((int)Bell::Key::A) * deltaTime * 1.0f;

    m_SquareScale += Bell::Input::IsKeyPressed((int)Bell::Key::Equal) * deltaTime;
    m_SquareScale -= Bell::Input::IsKeyPressed((int)Bell::Key::Minus) * deltaTime;

    m_Rotation += Bell::Input::IsKeyPressed((int)Bell::Key::Q) * deltaTime * 45.0f;
    m_Rotation -= Bell::Input::IsKeyPressed((int)Bell::Key::E) * deltaTime * 45.0f;

    Bell::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
    Bell::RenderCommand::Clear();

    SendPlayerPosition({ m_SquarePosition.x, m_SquarePosition.y, 0 });
    SendPlayerScale({ m_SquareScale.x, m_SquareScale.y, 1 });
    SendPlayerRotation(m_Rotation);

    Bell::Renderer2D::BeginScene(m_CameraController.GetCamera());
    for (auto& ent : m_Client.m_Entities)
    {
        if (ent.active && &ent != m_Client.m_Player)
        {
            Bell::Renderer2D::DrawQuad(ent.position, ent.scale, ent.rotation, m_Texture, m_SquareColor, m_TextureScale);
        }
    }

    Bell::Renderer2D::DrawQuad(m_SquarePosition, m_SquareScale, m_Rotation, m_Texture, m_SquareColor, m_TextureScale);
    Bell::Renderer2D::EndScene();
}

void ClientLayer::OnEvent(Bell::Event& e)
{
}

void ClientLayer::OnImGuiRender()
{
    ImGui::Begin("Network Info");

    for (auto& ent : m_Client.m_Entities)
    {
        if (ent.active && &ent != m_Client.m_Player) {
            ImGui::DragFloat3("Entity position: ", glm::value_ptr(ent.position), 0.01f);
            ImGui::DragFloat3("Entity Scale: ", glm::value_ptr(ent.scale), 0.01f);
            ImGui::DragFloat("Entity Scale: ", &ent.rotation, 0.01f);
        }
    }

    ImGui::End();

}

void ClientLayer::OnPlayerJoin(Bell::Packet& packet)
{
    Bell::peer_id_t id;
    packet >> id;
    m_Client.m_Entities[id].active = true;

    B_CORE_INFO("Player Joined, Client ID: {0}", (int)id);
}

void ClientLayer::OnPlayerLeave(Bell::Packet& packet)
{
    Bell::peer_id_t id;
    packet >> id;
    m_Client.m_Entities[id].active = false;

    B_CORE_INFO("Player Left, Client ID: {0}", (int)id);
}

void ClientLayer::OnSnapshot(Bell::Packet& packet)
{
    int16_t updateEntityCount = 0;
    packet >> updateEntityCount;
    for (int16_t i = 0; i < updateEntityCount; i++)
    {
        Bell::peer_id_t id = 0;
        float x, y, z;
        float sx, sy, sz;
        float r;

        packet >> id;
        packet >> x >> y >> z;
        packet >> sx >> sy >> sz;
        packet >> r;
        if (id != m_Client.GetPeerID())
        {
            auto* p = &m_Client.m_Entities[id];
            p->position = { x, y, z };
            p->scale = { sx, sy, sz };
            p->rotation = r;
            p->active = true;
        }
    }
}

void ClientLayer::OnSpawnPoint(Bell::Packet& packet)
{
    if (m_Client.m_Player)
    {
        packet >> m_Client.m_Player->position.x
            >> m_Client.m_Player->position.y
            >> m_Client.m_Player->position.z;
    }
}

void ClientLayer::SendPlayerPosition(const glm::vec3& position)
{
    Bell::Packet packet;
    packet << Bell::ServerCommand::PlayerPosition
        << m_Client.GetPeerID()
        << position.x << position.y << position.z;

    m_Client.QueueSendToPeer(m_Client.m_ServerPeer, packet, 0, 0);
}

void ClientLayer::SendPlayerScale(const glm::vec3& scale)
{
    Bell::Packet packet;
    packet << Bell::ServerCommand::PlayerScale
        << m_Client.GetPeerID()
        << scale.x << scale.y << scale.z;

    m_Client.QueueSendToPeer(m_Client.m_ServerPeer, packet, 0, 0);
}

void ClientLayer::SendPlayerRotation(float& rotation)
{
    Bell::Packet packet;
    packet << Bell::ServerCommand::PlayerRotation
        << m_Client.GetPeerID()
        << rotation;

    m_Client.QueueSendToPeer(m_Client.m_ServerPeer, packet, 0, 0);
}
