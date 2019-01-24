#ifndef SOCKET_H
#define SOCKET_H

#include "Bell/Core.h"
#include <WinSock2.h>

typedef unsigned int uint32;

namespace Bell
{
    const uint32 SOCKET_BUFFER_SIZE = 1024;

    class BELL_API Socket
    {
    public:
        bool CreateSocket();
        bool BindSocket();

        bool ReceivePackets();

    private:
        SOCKET sock;

        int s_AddressFamily = AF_INET; // IPv4
        int s_Type = SOCK_DGRAM; // UDP
        int s_Protocol = IPPROTO_UDP;
    };
}

#endif // !SOCKET_H
