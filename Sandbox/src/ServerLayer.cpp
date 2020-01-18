#include "ServerLayer.h"

#include "Bell/Networking/Network.h"

ServerLayer::ServerLayer()
    : Layer("Server Layer")
{
    
}

void ServerLayer::OnAttach()
{
    if (!m_Server.CreateAsServer(2))
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
