#include "ClientLayer.h"
#include <imgui/imgui.h>
#include <glm/gtc/type_ptr.hpp>

#include "Bell/Networking/Network.h"
#include "Bell/Networking/NetworkHost.h"
#include "Bell/Networking/NetworkConstants.h"

#include "Bell/Networking/Packet/Packet.h"
#include "Bell/Networking/Packet/PacketFuncHandler.h"

ClientLayer::ClientLayer()
    : Layer("Client Layer"), m_CameraController(1200.0f / 720.0f, false)
{
    B_PACKET_FUNCTION_DEF(Bell::ClientCommand::PlayerJoin, ClientLayer::OnPlayerJoin);
    B_PACKET_FUNCTION_DEF(Bell::ClientCommand::PlayerLeave, ClientLayer::OnPlayerLeave);
    B_PACKET_FUNCTION_DEF(Bell::ClientCommand::Snapshot, ClientLayer::OnSnapshot);

    B_PACKET_FUNCTION_DEF(Bell::ClientCommand::SpawnPoint, ClientLayer::OnSpawnPoint);
}

void ClientLayer::OnAttach()
{
    auto peer = m_Client.CreateAsClient(Bell::LOCAL_HOST);
    //B_ASSERT(!peer, "Peer could not be created as Client");

    m_Client.mp_ServerPeer = *peer;

    m_Client.mp_Player = &m_Client.m_Entities[m_Client.GetPeerID()];

    m_Texture = Bell::Texture2D::Create("assets/textures/bigmisssteak.png");
}

void ClientLayer::OnDetach()
{
}

void ClientLayer::OnUpdate(Bell::Timestep deltaTime)
{
    m_Client.Tick();

    //m_CameraController.OnUpdate(deltaTime);

    m_SquarePosition.y += Bell::Input::IsKeyPressed((int)Bell::Key::W) * deltaTime * 1.0f;
    m_SquarePosition.y -= Bell::Input::IsKeyPressed((int)Bell::Key::S) * deltaTime * 1.0f;

    m_SquarePosition.x += Bell::Input::IsKeyPressed((int)Bell::Key::D) * deltaTime * 1.0f;
    m_SquarePosition.x -= Bell::Input::IsKeyPressed((int)Bell::Key::A) * deltaTime * 1.0f;

    Bell::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
    Bell::RenderCommand::Clear();

    SendPlayerPosition({ m_SquarePosition.x, m_SquarePosition.y, 0 });

    Bell::Renderer2D::BeginScene(m_CameraController.GetCamera());
    for (auto& ent : m_Client.m_Entities)
    {
        if (ent.active && &ent != m_Client.mp_Player)
        {
            Bell::Renderer2D::DrawQuad(ent.position, m_SquareScale, m_Rotation, m_Texture, m_SquareColor, m_TextureScale);
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
    ImGui::Begin("Sandbox 2D Settings");

    for (auto& ent : m_Client.m_Entities)
    {
        if (ent.active && &ent != m_Client.mp_Player)
            ImGui::DragFloat2("Entity position: ", glm::value_ptr(ent.position), 0.01f);
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
        float x, y;
        packet >> id;
        packet >> x >> y;
        if (id != m_Client.GetPeerID())
        {
            auto* p = &m_Client.m_Entities[id];
            p->position = { x, y, 0 };
            p->active = true;
        }
    }
}

void ClientLayer::OnSpawnPoint(Bell::Packet& packet)
{
    if (m_Client.mp_Player)
    {
        packet >> m_Client.mp_Player->position.x
            >> m_Client.mp_Player->position.y;
    }
}

void ClientLayer::SendPlayerPosition(const glm::vec3& position)
{
    Bell::Packet packet;
    packet << Bell::ServerCommand::PlayerPosition
        << m_Client.GetPeerID()
        << position.x << position.y;

    m_Client.QueueSendToPeer(m_Client.mp_ServerPeer, packet, 0, 0);
}
