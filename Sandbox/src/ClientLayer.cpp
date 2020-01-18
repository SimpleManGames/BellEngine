#include "ClientLayer.h"

#include "Bell/Networking/NetworkHost.h"
#include "Bell/Networking/NetworkConstants.h"

ClientLayer::ClientLayer()
    : Layer("Client Layer")
{
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
    
}

void ClientLayer::OnEvent(Bell::Event& e)
{

}
