#ifndef _CLIENT_CONFIG_H
#define _CLIENT_CONFIG_H

#include "Bell/Networking/NetworkConstants.h"

namespace Bell
{
    struct ClientConfig
    {
        // Will hold client options when supported
        std::string serverIP = LOCAL_HOST;

        std::string title;
        unsigned int width;
        unsigned int height;
    };
}

#endif // !_CLIENT_CONFIG_H
