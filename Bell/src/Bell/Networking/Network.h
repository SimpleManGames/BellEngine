#ifndef _NETWORK_H
#define _NETWORK_H

#include <enet/enet.h>
#include "Bell/Core/Config.h"
#include "Bell/Networking/NetworkConstants.h"
#include "Bell/Networking/Packet/PacketFuncHandler.h"

namespace Bell
{
    class Network
    {
    public:
        static void Init();
        static void Shutdown();

        static ENetHost* CreateHost(const ENetAddress* address, int connections);
        static ENetPeer* ConnectHostTo(ENetHost* host, const std::string& ip);
        static int GetPeerIDFromServer(ENetHost* host);
        static ENetPacket* CreatePacket(Packet packet, uint32_t flags);

        static PacketFuncHandler& GetPacketFunctionHandler() { return m_PacketFuncHandler; }

    private:
        static PacketFuncHandler& m_PacketFuncHandler;
    };
}

#endif // !_NETWORK_H