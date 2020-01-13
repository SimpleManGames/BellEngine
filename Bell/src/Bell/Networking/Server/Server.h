#ifndef _SERVER_H
#define _SERVER_H

#include "Bell/Networking/NetworkHost.h"
#include "Bell/Networking/NetworkConstants.h"

namespace Bell
{
    struct ServerEntity
    {
        glm::vec3 position{ 0.0f };
        bool active = false;
    };

    struct ConnectedClient
    {
        ENetPeer* peer = nullptr;
        peer_id_t entityID;
        bool connected = false;
    };

    class Server : public NetworkHost
    {
    public:
        Server()
            : NetworkHost("Server")
        {

        }
        void Update();

    private:
        virtual void OnPeerConnect(ENetPeer* peer) override;
        virtual void OnPeerDisconnect(ENetPeer* peer) override;
        virtual void OnPeerTimeout(ENetPeer* peer) override;
        virtual void OnCommandReceive(ENetPeer* peer, Packet& packet, command_t command) override;

        void HandleCommandPlayerPosition(Packet& packet);

        int FindEmptySlot() const;

        void AddPeer(ENetPeer* peer, peer_id_t id);
        void RemovePeer(uint32_t connectionID);

        std::array<ServerEntity, 512> m_Entities;
        std::array<ConnectedClient, MAX_CONNECTIONS> m_ConnectedClients{};

        bool m_IsRunning = true;
    };
}

#endif // !_SERVER_H