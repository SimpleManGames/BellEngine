#ifndef SOCKET_H
#define SOCKET_H

#include "Bell/Core.h"
#include <WinSock2.h>

namespace Bell
{
    class BELL_API Socket
    {
    public:
        bool CreateSocket();
        bool BindSocket();

    private:
        SOCKET sock;

        int s_AddressFamily = AF_INET; // IPv4
        int s_Type = SOCK_DGRAM; // UDP
        int s_Protocol = IPPROTO_UDP;
    };
}

#endif // !SOCKET_H
