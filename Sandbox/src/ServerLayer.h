#ifndef _SERVER_LAYER_H
#define _SERVER_LAYER_H

#include <atomic>

#include <Bell.h>

class ServerLayer : public Bell::Layer
{
public:
    ServerLayer();
    virtual ~ServerLayer() = default;

    virtual void OnAttach();
    virtual void OnDetach();

    void OnUpdate(Bell::Timestep deltaTime) override;
private:
    //Bell::Server m_Server;
    std::atomic<bool> m_ServerRunning = true;
    std::atomic<bool> m_ServerConsoleRunning = true;
};

#endif // !_SERVER_LAYER_H