#include "ServerLayer.h"

#include "Bell/Networking/Network.h"
#include "Bell/Networking/Packet/PacketFuncHandler.h"
#include "Bell/Networking/Packet/Packet.h"

ServerLayer::ServerLayer()
    : Layer("Server Layer")
{
    B_PACKET_FUNCTION_DEF(Bell::ServerCommand::PlayerPosition, ServerLayer::HandlePlayerPosition);
}

void ServerLayer::OnAttach()
{
    if (!m_Server.CreateAsServer(4))
    {
        B_ASSERT(true, "Failed to create server!");
        return;
    }

    B_TRACE("Successfully created Server");
}

void ServerLayer::OnDetach()
{
    
}

void ServerLayer::OnUpdate(Bell::Timestep deltaTime)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(20));

    if (m_ServerRunning) {
        m_Server.Tick();
        m_Server.Update();

        m_Clock += deltaTime.GetMilliseconds();
        if (m_Server.GetConnectedPeerCount() == 0)
            m_ServerRunning = m_Clock < 8000;
        else
            m_Clock = 0;
    }
    else
        m_Server.DisconnectAllPeers();
}

void ServerLayer::HandlePlayerPosition(Bell::Packet& packet)
{
    Bell::peer_id_t id;
    packet >> id;
    packet >> m_Server.m_Entities[id].position.x
        >> m_Server.m_Entities[id].position.y
        >> m_Server.m_Entities[id].position.z;
}