// Entry Point definition for application using the Bell Engine
// ------------------------------------------------------------

#ifndef _ENTRY_POINT_H
#define _ENTRY_POINT_H

#ifdef B_PLATFORM_WINDOWS

#include <Bell/Networking/NetworkConstants.h>
#include <Bell/Core/Config.h>

#include <vector>

typedef std::vector<std::pair<std::string, std::string>> Args;

// This function definition will be defined in user applications
extern Bell::Application* Bell::CreateApplication(Bell::Config config);

// Prototype
Bell::Config CreateConfigFromArgs(int argc, char** argv);

int main(int argc, char** argv)
{
    // Initialize the logger
    Bell::Log::Init();
    B_CORE_INFO("Initialized Log!");
    B_INFO("Initialized Log!");

    Bell::Config config = CreateConfigFromArgs(argc, argv);

    B_PROFILE_BEGIN_SESSION("Startup", "logs/BellProfile-Startup.json");
    // Create app using the app user's function
    auto app = Bell::CreateApplication(config);
    B_PROFILE_END_SESSION();

    B_PROFILE_BEGIN_SESSION("Runtime", "logs/BellProfile-Runtime.json");
    app->Run();
    B_PROFILE_END_SESSION();

    B_PROFILE_BEGIN_SESSION("Shutdown", "logs/BellProfile-Shutdown.json");
    delete app;
    B_PROFILE_END_SESSION();
}

Bell::Config CreateConfigFromArgs(int argc, char** argv)
{
    Bell::Config config;

    Args args;
    for (int i = 0; i < argc; i++)
        if (argv[i][0] == '-' && argc > i + 1)
            args.emplace_back(argv[i], argv[i + 1]);

    for (const auto& option : args)
    {
        if (option.first == "-server")
        {
            config.launchType = Bell::LaunchType::Server;

            try
            {
                int maxConnections = std::stoi(option.second);
                if (maxConnections < Bell::MIN_CONNECTIONS)
                {
                    throw std::invalid_argument(
                        "Max Connections must be at least" +
                        std::to_string(Bell::MIN_CONNECTIONS) + ".\n");
                }
                else if (maxConnections > Bell::MAX_CONNECTIONS)
                {
                    throw std::invalid_argument("Max connections must be " +
                        std::to_string(Bell::MAX_CONNECTIONS) + " or below.\n");
                }
            }
            catch (std::invalid_argument & e)
            {
                B_CORE_WARN("Unable to set max connections, defaulting to 4. Reason: {0}", e.what());
                config.serverOptions.maxConnections = 4;
            }
        }
        else if (option.first == "-client")
            config.launchType = Bell::LaunchType::Client;
        else 
            config.launchType = Bell::LaunchType::None;
    }

    return config;
}

#endif // !B_PLATFORM_WINDOWS

#endif // !_ENTRY_POINT_H