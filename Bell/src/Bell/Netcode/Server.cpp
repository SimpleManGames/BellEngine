#include "bpch.h"
#include "Server.h"

namespace Bell
{
    bool Server::Start(WORD winsock_version)
    {
        WSADATA winsock_data;
        if (WSAStartup(winsock_version, &winsock_data))
        {
            B_CORE_ASSERT("WSAStartup failed: %d", WSAGetLastError());
            return false;
        }

        return true;
    }

    bool Server::Close()
    {
        if (WSACleanup())
        {
            B_CORE_ASSERT("WSACleanup failed: %d", WSAGetLastError());
            return false;
        }

        return true;
    }
}