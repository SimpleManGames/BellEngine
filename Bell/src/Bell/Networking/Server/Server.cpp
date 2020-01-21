#include "bpch.h"
#include "Server.h"

#include "Bell/Networking/Network.h"
#include <Bell\Networking\NetworkCommand.h>
#include <Bell/Networking/Packet/PacketFuncHandler.h>

namespace Bell
{
    void Server::Update()
    {
        Packet packet;
        uint16_t count = NetworkHost::GetConnectedPeerCount();
        packet << ClientCommand::Snapshot << count;
        for (int i = 0; i < NetworkHost::GetMaxConnections(); i++)
        {
            if (m_ConnectedClients[i].connected)
            {
                packet << static_cast<peer_id_t>(i)
                    << m_Entities[i].position.x
                    << m_Entities[i].position.y;
            }
        }

        QueueBroadcastToPeers(packet, 0, 0);
    }

    void Server::OnPeerConnect(ENetPeer* peer)
    {
        int slot = FindEmptySlot();
        if (slot >= 0)
        {
            peer_id_t id = static_cast<peer_id_t>(slot);

            // Send the client back their ID
            Packet packet;
            packet << ClientCommand::PeerID << id;
            NetworkHost::QueueSendToPeer(peer, packet, 0, ENET_PACKET_FLAG_RELIABLE);

            Packet announcement;
            announcement << ClientCommand::PlayerJoin << id;
            QueueBroadcastToPeers(announcement, 0, ENET_PACKET_FLAG_RELIABLE);

            AddPeer(peer, id);

            Packet spawn;
            auto& player = m_Entities[id];
            player.position = glm::vec3{ 0.0f };
            spawn << ClientCommand::SpawnPoint << player.position.x
                << player.position.y << player.position.z;
            QueueSendToPeer(peer, spawn, 0, ENET_PACKET_FLAG_RELIABLE);
        }
    }

    void Server::OnPeerDisconnect(ENetPeer* peer)
    {
        RemovePeer(peer->connectID);
    }

    void Server::OnPeerTimeout(ENetPeer* peer)
    {
        RemovePeer(peer->connectID);
    }

    void Server::OnCommandReceive(ENetPeer* peer, Packet& packet, command_t command)
    {
        Network::GetPacketFunctionHandler().GetPacketFunction(command)(packet);
    }
    
    int Server::FindEmptySlot() const
    {
        for (int i = 0; i < NetworkHost::GetMaxConnections(); i++)
            if (!m_ConnectedClients[i].connected)
                return i;

        return -1;
    }

    void Server::AddPeer(ENetPeer* peer, peer_id_t id)
    {
        B_CORE_INFO("New Peer, Peer ID: {0}", (int)id);
        m_ConnectedClients[id].peer = peer;
        m_ConnectedClients[id].connected = true;
        m_ConnectedClients[id].entityID = id;
    }

    void Server::RemovePeer(uint32_t connectionID)
    {
        auto itr = std::find_if(
            m_ConnectedClients.begin(), m_ConnectedClients.end(), [this, &connectionID](auto& conn)
            {
                return conn.peer && conn.peer->connectID == connectionID;
            });

        B_CORE_ASSERT(itr != m_ConnectedClients.cend(), "Couldn't find Peer to remove");
        if (itr != m_ConnectedClients.cend())
        {
            B_CORE_INFO("Client Disconnected, Peer ID:{0}", (int)itr->entityID);
            m_Entities[itr->entityID].active = false;
            itr->connected = false;
            itr->peer = nullptr;

            Packet announcement;
            announcement << ClientCommand::PlayerLeave << itr->entityID;
            QueueBroadcastToPeers(announcement, 0, ENET_PACKET_FLAG_RELIABLE);

            itr->entityID = 0;
        }
    }
}