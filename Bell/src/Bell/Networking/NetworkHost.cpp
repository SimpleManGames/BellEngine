#include "bpch.h"
#include "NetworkHost.h"

#include "Bell/Networking/NetworkCommand.h"
#include "Bell/Networking/NetworkConstants.h"

namespace Bell
{
    ENetHost* CreateHost(const ENetAddress* address, int connections)
    {
        B_PROFILE_FUNCTION();
        // http://enet.bespin.org/group__host.html#ga5567a95d7a45521dc9cba93a9066c940
        return enet_host_create(address, connections, 2, 0, 0);
    }

    ENetPeer* ConnectHostTo(ENetHost* host, const std::string& ip)
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

    int GetPeerIDFromServer(ENetHost* host)
    {
        int id = -1;
        ENetEvent event;

        // Wait 2 seconds for an event
        while (enet_host_service(host, &event, 2000) > 0 && event.type == ENET_EVENT_TYPE_RECEIVE)
        {
            ClientCommand command;
            ENetPacket* packet = enet_packet_create(event.packet->data, event.packet->dataLength + 1, ENET_PACKET_FLAG_RELIABLE);
            *packet >> command;
            if (command == ClientCommand::PeerID)
            {
                peer_id_t peerID;
                *packet >> peerID;
                id = peerID;
                break;
            }
        }
        return id;
    }
}