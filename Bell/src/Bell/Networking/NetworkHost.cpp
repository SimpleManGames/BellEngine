#include "bpch.h"
#include "NetworkHost.h"

#include "Bell/Networking/Packet.h"
#include "Bell/Networking/Network.h"
#include "Bell/Networking/NetworkTypes.h"
#include "Bell/Networking/NetworkCommand.h"
#include "Bell/Networking/NetworkConstants.h"

namespace Bell
{
    NetworkHost::~NetworkHost()
    {
        enet_host_destroy(mp_Host);
    }

    std::optional<ENetPeer*> NetworkHost::CreateAsClient(const std::string& ip)
    {
        /// http://enet.bespin.org/Tutorial.html#CreateClient

        mp_Host = Network::CreateHost(0, 1);
        if (!mp_Host)
        {
            B_CORE_ERROR("Failed to CreateHost");
            return {};
        }

        auto server = Network::ConnectHostTo(mp_Host, ip);
        if (!server)
        {
            B_CORE_ERROR("Failed to connect to server! (Game Full)");
            return {};
        }
        Flush();

        int id = Network::GetPeerIDFromServer(mp_Host);
        if (id == -1)
        {
            B_CORE_ERROR("Peer ID was not received from the server!");
            return {};
        }

        m_PeerID = static_cast<peer_id_t>(id);
        return server;
    }

    bool NetworkHost::CreateAsServer(int maxConnections)
    {
        /// http://enet.bespin.org/Tutorial.html#CreateServer

        m_MaxConnections = maxConnections;
        ENetAddress address{};
        address.host = ENET_HOST_ANY;
        address.port = DEFAULT_PORT;
        mp_Host = Network::CreateHost(&address, maxConnections);
        return mp_Host;
    }

    void NetworkHost::DisconnectFromPeer(ENetPeer* peer)
    {
        /// http://enet.bespin.org/Tutorial.html#Disconnecting

        enet_peer_disconnect(peer, static_cast<uint32_t>(m_PeerID));
        ENetEvent event;
        while (enet_host_service(mp_Host, &event, 3000) > 0)
        {
            switch (event.type)
            {
                case ENET_EVENT_TYPE_RECEIVE:
                    enet_packet_destroy(event.packet);
                    break;
                case ENET_EVENT_TYPE_DISCONNECT:
                    Flush();
                    break;

                default:
                    break;
            }
        }
        enet_peer_reset(peer);
    }

    void NetworkHost::DisconnectAllPeers()
    {
        int maxConnections = GetConnectedPeerCount();
        int connections = maxConnections;
        for (int i = 0; i < maxConnections; i++)
        {
            enet_peer_disconnect(&mp_Host->peers[i], 0);
        }

        ENetEvent event;
        while (enet_host_service(mp_Host, &event, 1000) > 0 && connections > 0)
        {
            switch (event.type)
            {
                case ENET_EVENT_TYPE_RECEIVE:
                    enet_packet_destroy(event.packet);
                    break;
                case ENET_EVENT_TYPE_DISCONNECT:
                    connections--;
                    break;

                default:
                    break;
            }
        }
    }

    int NetworkHost::GetConnectedPeerCount() const
    {
        return mp_Host->connectedPeers;
    }

    peer_id_t NetworkHost::GetPeerID() const
    {
        return m_PeerID;
    }

    int NetworkHost::GetMaxConnections() const
    {
        return m_MaxConnections;
    }

    void NetworkHost::QueueSendToPeer(ENetPeer* peer, const void * packet, uint8_t channel, uint32_t flags)
    {
        ENetPacket* ePacket = Network::CreatePacket(packet, flags);
        QueuedPacket qPacket;
        qPacket.packet = ePacket;
        qPacket.peer = peer;
        qPacket.style = QueuedPacket::Style::One;
        qPacket.channel = channel;
        m_Queue.push_back(qPacket);
    }

    void NetworkHost::QueueBroadcastToPeers(const void * packet, uint8_t channel, uint32_t flags)
    {
        ENetPacket* ePacket = Network::CreatePacket(packet, flags);
        QueuedPacket qPacket;
        qPacket.packet = ePacket;
        qPacket.style = QueuedPacket::Style::Broadcast;
        qPacket.channel = channel;
        m_Queue.push_back(qPacket);
    }

    void NetworkHost::RemovePeerFromPacketQueue(ENetPeer* peer)
    {
        for (auto itr = m_Queue.cbegin(); itr != m_Queue.cend();)
        {
            if (itr->style == QueuedPacket::Style::One && itr->peer->connectID == peer->connectID)
                itr = m_Queue.erase(itr);
            else
                itr++;
        }
    }
     
    void NetworkHost::OnCommandRecieve(ENetPeer* peer, const ENetPacket& ePacket)
    {
        // Convert from our packet to enet packet

        Packet packet;
        packet.Append(ePacket.data, ePacket.dataLength);
        command_t command;
        packet >> command;
        OnCommandReceive(peer, packet, command);
    }

    void NetworkHost::Flush()
    {
        /// http://enet.bespin.org/group__host.html#gac8f53bcdbd540043f87e7d59048559fa
        enet_host_flush(mp_Host);
    }

}