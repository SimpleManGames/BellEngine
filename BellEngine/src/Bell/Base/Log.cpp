#include "bpch.h"
#include "Bell/Base/Log.h"

#include "spdlog/sinks/stdout_color_sinks.h"

namespace Bell
{

    Ref<spdlog::logger> Log::s_CoreLogger;
    Ref<spdlog::logger> Log::s_ClientLogger;

    void Log::Init(const std::string &coreName, const std::string &appName)
    {
        B_PROFILE_FUNCTION();
        // Set spdlog definition for the way displayed in the console
        // [Time] LoggerName: Message
        spdlog::set_pattern("%^[%T] %n: %v%$");

        // TODO: Pull this duped code into a function

        // Try to get a logger with the same name
        s_CoreLogger = spdlog::get(coreName);
        // If one doesn't exist, create it
        if (s_CoreLogger == nullptr)
        {
            // Create and set the core's logger
            s_CoreLogger = spdlog::stdout_color_mt(coreName);
            s_CoreLogger->set_level(spdlog::level::trace);
        }

        // Try to get a logger with the same name
        s_ClientLogger = spdlog::get(appName);
        // If one doesn't exist, create it
        if (s_ClientLogger == nullptr)
        {
            // Create and set the app's logger
            s_ClientLogger = spdlog::stdout_color_mt(appName);
            s_ClientLogger->set_level(spdlog::level::trace);
        }
    }

    void Log::Shutdown()
    {
        spdlog::shutdown();
    }
}