#include "bpch.h"
#include "NetworkHost.h"

#include "Bell/Networking/Network.h"
#include "Bell/Networking/Packet/Packet.h"

namespace Bell
{
    NetworkHost::~NetworkHost()
    {
        enet_host_destroy(mp_Host);
    }

    void NetworkHost::Tick()
    {
        const int MAX_SEND_LIMIT = 1024;

        int bytesSent = 0;

        while (!m_Queue.empty())
        {
            auto qPacket = m_Queue.front();
            m_Queue.pop_front();
            bytesSent += (int)qPacket.packet->dataLength;

            switch (qPacket.style)
            {
                case QueuedPacket::Style::Broadcast:
                    enet_host_broadcast(mp_Host, qPacket.channel, qPacket.packet);
                    break;
                case QueuedPacket::Style::One:
                    enet_peer_send(qPacket.peer, qPacket.channel, qPacket.packet);
                    break;

                default:
                    break;
            }

            Flush();
            if (bytesSent > MAX_SEND_LIMIT)
                break;
        }
        
        B_CORE_ASSERT(mp_Host, "Network Host is invalid!");
        ENetEvent event;
        while (enet_host_service(mp_Host, &event, 0) > 0)
        {
            switch (event.type)
            {
                case ENET_EVENT_TYPE_CONNECT:
                    OnPeerConnect(event.peer);
                    break;
                case ENET_EVENT_TYPE_RECEIVE:
                    OnCommandRecieve(event.peer, *event.packet);
                    enet_packet_destroy(event.packet);
                    break;
                case ENET_EVENT_TYPE_DISCONNECT:
                    RemovePeerFromPacketQueue(event.peer);
                    OnPeerDisconnect(event.peer);
                    break;
                case ENET_EVENT_TYPE_NONE:
                    break;

                default:
                    break;
            }
        }
    }

    std::optional<ENetPeer*> NetworkHost::CreateAsClient(const std::string& ip)
    {
        /// http://enet.bespin.org/Tutorial.html#CreateClient

        mp_Host = Network::CreateHost(NULL, 1);
        if (mp_Host == NULL)
        {
            B_CORE_ERROR("Failed to CreateHost");
            return {};
        }

        auto server = Network::ConnectHostTo(mp_Host, ip);
        if (!server)
        {
            B_CORE_ERROR("Failed to connect to server!");
            return {};
        }
        Flush();

        int id = Network::GetPeerIDFromServer(mp_Host);
        if (id == -1)
        {
            B_CORE_ERROR("Peer ID was not received from the server!");
            return {};
        }

        B_CORE_INFO("Created Client with IP Address of {0}", ip);
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
        return (int)mp_Host->connectedPeers;
    }

    peer_id_t NetworkHost::GetPeerID() const
    {
        return m_PeerID;
    }

    int NetworkHost::GetMaxConnections() const
    {
        return m_MaxConnections;
    }

    void NetworkHost::QueueSendToPeer(ENetPeer* peer, Packet& packet, uint8_t channel, uint32_t flags)
    {
        ENetPacket* ePacket = Network::CreatePacket(packet, flags);
        QueuedPacket qPacket;
        qPacket.packet = ePacket;
        qPacket.peer = peer;
        qPacket.style = QueuedPacket::Style::One;
        qPacket.channel = channel;
        m_Queue.push_back(qPacket);
    }

    void NetworkHost::QueueBroadcastToPeers(Packet& packet, uint8_t channel, uint32_t flags)
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