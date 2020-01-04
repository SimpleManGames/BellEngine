#include "bpch.h"
#include "Network.h"

namespace Bell
{
    void Network::Init()
    {
        B_PROFILE_FUNCTION();

        if (enet_initialize() != 0)
            B_CORE_ERROR("An error has occurred while initializing Enet!");
    }

    void Network::Shutdown()
    {
        B_PROFILE_FUNCTION();

        atexit(enet_deinitialize);
    }

    void Network::LaunchServer(const ServerConfig& config)
    {
        B_CORE_INFO("Launching Server");
        // TODO:
    }
}
