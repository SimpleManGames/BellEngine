#ifndef _CLIENT_H
#define _CLIENT_H

#include "Bell/Networking/NetworkHost.h"

extern class ClientLayer;

namespace Bell
{
    // TODO: Make proper Entity
    struct Entity final {
        glm::vec3 position{ 0.0f };
        bool active = false;
    };

    class Client : public NetworkHost
    {
        Client()
            : NetworkHost("Client")
        {

        }

        friend class ClientLayer;
        
    private:
        virtual void OnPeerConnect(ENetPeer* peer) override;
        virtual void OnPeerDisconnect(ENetPeer* peer) override;
        virtual void OnPeerTimeout(ENetPeer* peer) override;
        virtual void OnCommandReceive(ENetPeer* peer, Packet& packet, command_t command) override;

        ENetPeer* mp_ServerPeer = nullptr;
        std::array<Entity, 512> m_Entities;
        Entity* mp_Player = nullptr;
    };
}

#endif // !_CLIENT_H