#include "bpch.h"
#include "Socket.h"

namespace Bell
{
    bool Socket::CreateSocket()
    {
        sock = socket(s_AddressFamily, s_Type, s_Protocol);

        if (sock == INVALID_SOCKET)
        {
            B_CORE_ASSERT("Socket creation failed: %d", WSAGetLastError());
            return false;
        }

        return true;
    }

    bool Socket::BindSocket()
    {
        SOCKADDR_IN localAddress;
        localAddress.sin_family = s_AddressFamily;
        localAddress.sin_port = htons(9999); // Converts the port bytes of 9999 to big-endian
        localAddress.sin_addr.s_addr = INADDR_ANY; // Allows the socket to accept packets on all interfaces

        if (bind(sock, (SOCKADDR*)&localAddress, sizeof(localAddress)) == SOCKET_ERROR)
        {
            B_CORE_ASSERT("Bind Socket failed: %d", WSAGetLastError());
            return false;
        }

        return true;

    }
}