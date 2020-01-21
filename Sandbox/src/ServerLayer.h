#ifndef _SERVER_LAYER_H
#define _SERVER_LAYER_H

#include <atomic>

#include <Bell.h>
#include <Bell/Networking/Server/Server.h>

class Bell::Packet;

class ServerLayer : public Bell::Layer
{
public:
    ServerLayer();
    virtual ~ServerLayer() = default;

    virtual void OnAttach();
    virtual void OnDetach();

    void OnUpdate(Bell::Timestep deltaTime) override;
private:

    float m_Clock = 0;
    Bell::Server m_Server;
    std::atomic<bool> m_ServerRunning = true;
    std::atomic<bool> m_ServerConsoleRunning = true;

    void HandlePlayerPosition(Bell::Packet& packet);
    void HandlePlayerScale(Bell::Packet& packet);
};

#endif // !_SERVER_LAYER_H