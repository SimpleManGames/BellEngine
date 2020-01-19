#include "ClientLayer.h"

#include "Bell/Networking/Network.h"
#include "Bell/Networking/NetworkHost.h"
#include "Bell/Networking/NetworkConstants.h"

#include "Bell/Networking/Packet/Packet.h"
#include "Bell/Networking/Packet/PacketFuncHandler.h"

ClientLayer::ClientLayer()
    : Layer("Client Layer")
{
    B_PACKET_FUNCTION_DEF(Bell::ClientCommand::PlayerJoin, ClientLayer::OnPlayerJoin);
    B_PACKET_FUNCTION_DEF(Bell::ClientCommand::PlayerLeave, ClientLayer::OnPlayerLeave);
    B_PACKET_FUNCTION_DEF(Bell::ClientCommand::Snapshot, ClientLayer::OnSnapshot);

    B_PACKET_FUNCTION_DEF(Bell::ClientCommand::SpawnPoint, ClientLayer::OnSpawnPoint);
}

void ClientLayer::OnAttach()
{
    auto peer = m_Client.CreateAsClient(Bell::LOCAL_HOST);
    B_ASSERT(!peer, "Peer could not be created as Client");

    m_Client.mp_ServerPeer = *peer;

    m_Client.mp_Player = &m_Client.m_Entities[m_Client.GetPeerID()];
}

void ClientLayer::OnDetach()
{
}

void ClientLayer::OnUpdate(Bell::Timestep deltaTime)
{
    m_Client.Tick();
    SendPlayerPosition({ 1, 1, 1 });
}

void ClientLayer::OnEvent(Bell::Event& e)
{

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
        packet >> id >> x >> y >> z;
        if (id != m_Client.GetPeerID())
        {
            auto* p = &m_Client.m_Entities[id];
            p->position = { x,y,z };
            p->active = true;
        }
    }
}

void ClientLayer::OnSpawnPoint(Bell::Packet& packet)
{
    if (m_Client.mp_Player)
    {
        packet >> m_Client.mp_Player->position.x 
            >> m_Client.mp_Player->position.y 
            >> m_Client.mp_Player->position.z;
    }
}

void ClientLayer::SendPlayerPosition(const glm::vec3& position)
{
    Bell::Packet packet;
    packet << Bell::ServerCommand::PlayerPosition
        << m_Client.GetPeerID()
        << position.x << position.y << position.z;

    m_Client.QueueSendToPeer(m_Client.mp_ServerPeer, packet, 0, 0);
}
