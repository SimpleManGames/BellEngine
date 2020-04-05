#ifndef _SANDBOX_SERVER_H
#define _SANDBOX_SERVER_H

#include <Bell.h>
#include "ServerLayer.h"

class SandboxServer : public Bell::Application
{
public:
    SandboxServer(unsigned int maxConnections)
        : Application({})
    {
        PushLayer(new ServerLayer(maxConnections));
    }
    ~SandboxServer() {}
};

#endif // !_SANDBOX_SERVER_H