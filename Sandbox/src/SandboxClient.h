#ifndef _SANDBOX_CLIENT_H
#define _SANDBOX_CLIENT_H

#include <Bell.h>
#include "ClientLayer.h"

class SandboxClient : public Bell::Application {
public:
    SandboxClient(const std::string ip)
    {
        //PushLayer(new ExampleLayer());
        PushLayer(new ClientLayer(ip));
    }
    ~SandboxClient() { }
};

#endif // !_SANDBOX_CLIENT_H