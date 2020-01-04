#ifndef _NETWORK_H
#define _NETWORK_H

#include <enet/enet.h>
#include "Bell/Networking/Client/ClientConfig.h"
#include "Bell/Networking/Server/ServerConfig.h"

namespace Bell
{
    enum class LaunchType
    {
        Server,
        Client,
        Both
    };

    struct Config
    {
        LaunchType launchType = LaunchType::Both;

        ServerConfig serverOptions;
        ClientConfig clientOptions;
    };

    class Network
    {
    public:
        static void Init();
        static void Shutdown();

        static void LaunchServer(const ServerConfig &config);
        static void LaunchClient(const ClientConfig &config);
        static void LaunchBoth(const Config& config);
    };
}

#endif // !_NETWORK_H