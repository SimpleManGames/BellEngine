#include "ServerLayer.h"

#include "Bell/Networking/Network.h"

ServerLayer::ServerLayer()
    : Layer("Server Layer")
{
}

void ServerLayer::OnAttach()
{
    Bell::Network::Init();
    //if (!m_Server.CreateAsServer(2))
    //{
    //    B_ASSERT(true, "Failed to create server!");
    //    return;
    //}
}

void ServerLayer::OnDetach()
{
    Bell::Network::Shutdown();
}

void ServerLayer::OnUpdate(Bell::Timestep deltaTime)
{
    //float clock = 0;
    //while (m_ServerRunning)
    //{
    //    std::this_thread::sleep_for(std::chrono::milliseconds(20));
    //
    //    m_Server.Tick();
    //    m_Server.Update();
    //
    //    clock += deltaTime.GetMilliseconds();
    //    if (m_Server.GetConnectedPeerCount() == 0)
    //        m_ServerRunning = clock < 8000;
    //    else
    //        clock = 0;
    //}
    //m_Server.DisconnectAllPeers();
}
