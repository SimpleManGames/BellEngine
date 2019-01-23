#ifndef SERVER_H

#include "Bell/Core.h"
#include <winsock2.h>

namespace Bell
{
    class BELL_API Server
    {
    public:
        bool Start(WORD winsock_version = 0x202);
        bool Close();
    };
}

#endif // !SERVER_H
