#ifndef _NETWORK_HOST_H
#define _NETWORK_HOST_H

#include <deque>
#include <string>
#include <optional>
#include <enet/enet.h>

#include <Bell.h>
#include "Bell/Common/macros.h"
#include "Bell/Networking/NetworkTypes.h"

namespace Bell
{
    struct QueuedPacket
    {
        enum class Style
        {
            One,
            Broadcast
        };

        ENetPeer* peer = nullptr;
        ENetPacket* packet = nullptr;
        Style style = Style::Broadcast;
        uint8_t channel = 0;
    };

    class NetworkHost
    {
        NON_COPYABLE(NetworkHost)
        NON_MOVABLE(NetworkHost)

    public:
        NetworkHost(std::string &&name);
        virtual ~NetworkHost();

        /// Runs one tick of the host
        /// Must be called once per frame
        void Tick();

        /// Creates this NetworkHost as a client
        std::optional<ENetPeer*> CreateAsClient(const std::string& ip);

        /// Creates this NetworkHost as a Server
        bool CreateAsServer(int maxConnections);

        /// Disconnects all current peers
        void DisconnectAllPeers();

        int GetConnectedPeerCount() const;
        peer_id_t GetPeerID() const;
        int GetMaxConnections() const;

    protected:
        void SendToPeer(ENetPeer* peer, ENetPacket& packet, uint8_t channel, uint32_t flags);
        void BroadcastToPeers(ENetPacket& packet, uint8_t channel, uint32_t flags);

    private:
        void RemovePeerFromPacketQueue(ENetPeer* peer);
        virtual void OnPeerConnect(ENetPeer* peer) = 0;
        virtual void OnPeerDisconnect(ENetPeer* peer) = 0;
        virtual void OnPeerTimeout(ENetPeer* peer) = 0;

        virtual void OnCommandReceive(ENetPeer* peer, ENetPacket& packet, command_t command) = 0;

        void Flush();

        std::deque<QueuedPacket> m_Queue;

        ENetHost* mp_Host = nullptr;
        const std::string m_Name;

        peer_id_t m_PeerID = 0;
        int m_MaxConnections = 0;
    };
}
#endif // !_NETWORK_HOST_H
