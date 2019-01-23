#ifndef BELLSERVER_H
#define BELLSERVER_H

#include "Bell/Core.h"
#include <WinSock2.h>

namespace Bell
{
    class BELL_API Server
    {
    public:
        bool Start(WORD winsock_version = 0x202);
        bool Close();
    };
}

#endif // !BELLSERVER_H
