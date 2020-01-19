#include "bpch.h"
#include "Network.h"

#include <Bell\Networking\NetworkCommand.h>

namespace Bell
{
    PacketFuncHandler& Network::m_PacketFuncHandler = PacketFuncHandler();

    void Network::Init()
    {
        B_PROFILE_FUNCTION();

        if (enet_initialize() != 0)
            B_CORE_ERROR("An error has occurred while initializing Enet!");

        B_CORE_INFO("Initialized ENet successfully");
    }

    void Network::Shutdown()
    {
        B_PROFILE_FUNCTION();

        atexit(enet_deinitialize);
    }

    void Network::LaunchServer(const ServerConfig& config)
    {
        B_CORE_INFO("Launching Server");
        // TODO: 
        // Flag this application as a server in order to remove
        // pointless funcs like renderering from the loop

        // New Thread
        // Start the server

    }
    ENetHost* Network::CreateHost(const ENetAddress* address, int connections)
    {
        B_PROFILE_FUNCTION();
        // http://enet.bespin.org/group__host.html#ga5567a95d7a45521dc9cba93a9066c940
        return enet_host_create(address, connections, 2, 0, 0);
    }

    ENetPeer* Network::ConnectHostTo(ENetHost* host, const std::string& ip)
    {
        // http://enet.bespin.org/Tutorial.html#Connecting

        B_PROFILE_FUNCTION();

        ENetAddress address{};
        address.port = DEFAULT_PORT;

        if (enet_address_set_host(&address, ip.c_str()) != 0)
        {
            B_CORE_ERROR("Failed to create address!");
            return nullptr;
        }

        ENetPeer* peer = enet_host_connect(host, &address, 2, 0);
        if (!peer)
        {
            B_CORE_ERROR("Failed to connect to server(Game Full).");
            return nullptr;
        }

        ENetEvent event;
        // Wait 5000 milliseconds for the connect event
        if (enet_host_service(host, &event, 5000) > 0 && event.type == ENET_EVENT_TYPE_CONNECT)
            return peer;
        else
        {
            B_CORE_ERROR("Failed to connect to the server!");
            enet_peer_reset(peer);
            return nullptr;
        }
    }

    int Network::GetPeerIDFromServer(ENetHost* host)
    {
        int id = -1;
        ENetEvent event;

        // Wait 2 seconds for an event
        while (enet_host_service(host, &event, 2000) > 0 && event.type == ENET_EVENT_TYPE_RECEIVE)
        {
            ClientCommand command;
            Packet packet;
            packet.Append(event.packet->data, event.packet->dataLength);
            packet >> command;
            if (command == ClientCommand::PeerID)
            {
                peer_id_t peerID;
                packet >> peerID;
                id = peerID;
                break;
            }
        }
        return id;
    }

    ENetPacket* Network::CreatePacket(const void* data, uint32_t flags)
    {
        return enet_packet_create(data, sizeof(data), flags);
    }
}
