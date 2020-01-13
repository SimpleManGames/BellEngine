#ifndef _NETWORK_H
#define _NETWORK_H

#include <enet/enet.h>
#include "Bell/Core/Config.h"
#include "Bell/Networking/NetworkConstants.h"

namespace Bell
{
    class Network
    {
    public:
        static void Init();
        static void Shutdown();

        static void LaunchServer(const ServerConfig &config);
        static void LaunchClient(const ClientConfig &config);
        static void LaunchBoth(const Config& config);

        static ENetHost* CreateHost(const ENetAddress* address, int connections);
        static ENetPeer* ConnectHostTo(ENetHost* host, const std::string& ip);
        static int GetPeerIDFromServer(ENetHost* host);
        static ENetPacket* CreatePacket(const void* data, uint32_t flags);
    };
}

#endif // !_NETWORK_H