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
    bool Socket::ReceivePackets()
    {
        char buffer[SOCKET_BUFFER_SIZE];
        int flags = 0;
        SOCKADDR_IN from;
        int fromSize = sizeof(from);
        int bytesReceived = recvfrom(sock, buffer, SOCKET_BUFFER_SIZE, flags, (SOCKADDR*)&from, &fromSize);

        if (bytesReceived == SOCKET_ERROR)
        {
            B_CORE_ASSERT("recvfrom returned SOCKET_ERROR: %d", WSAGetLastError());
            return false;
        }
        else
        {
            buffer[bytesReceived] = 0;
            B_CORE_INFO("%d.%d.%d.%d:%d - %s",
                from.sin_addr.S_un.S_un_b.s_b1,
                from.sin_addr.S_un.S_un_b.s_b2,
                from.sin_addr.S_un.S_un_b.s_b3,
                from.sin_addr.S_un.S_un_b.s_b4,
                ntohs(from.sin_port), buffer);
        }

        return true;
    }
}