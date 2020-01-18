#ifndef _CLIENT_LAYER_H
#define _CLIENT_LAYER_H

#include <Bell.h>
#include <Bell/Networking/Client/Client.h>

class ClientLayer : public Bell::Layer
{
    friend class Bell::Client;

public:
    ClientLayer();
    virtual ~ClientLayer() = default;

    virtual void OnAttach();
    virtual void OnDetach();

    void OnUpdate(Bell::Timestep deltaTime) override;
    void OnEvent(Bell::Event& e) override;
private:
    Bell::Client m_Client;
};

#endif // !_CLIENT_LAYER_H