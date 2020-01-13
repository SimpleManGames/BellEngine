#ifndef _CONFIG_H
#define _CONFIG_H

#include "Bell/Networking/Server/ServerConfig.h"
#include "Bell/Networking/Client/ClientConfig.h"

namespace Bell 
{
    enum class LaunchType
    {
        Server,
        Client,
        Both,
        None
    };

    struct Config
    {
        LaunchType launchType = LaunchType::None;

        ServerConfig serverOptions;
        ClientConfig clientOptions;
    };
}

#endif // !_CONGIF_H