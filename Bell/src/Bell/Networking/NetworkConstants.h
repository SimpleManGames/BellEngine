#ifndef _NETWORK_CONSTANTS_H
#define _NETWORK_CONSTANTS_H

#include <string>

#include "Bell/Networking/NetworkTypes.h"

namespace Bell
{
    constexpr port_t DEFAULT_PORT = 56355;
    constexpr int MIN_CONNECTIONS = 1;
    constexpr int MAX_CONNECTIONS = 8;
    const std::string LOCAL_HOST = "127.0.0.1";
}
#endif // !_NETWORK_CONSTANTS_H
