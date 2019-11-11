#include "bpch.h"
#include "Log.h"

#include "spdlog/sinks/stdout_color_sinks.h"

namespace Bell {

    Ref<spdlog::logger> Log::s_CoreLogger;
    Ref<spdlog::logger> Log::s_ClientLogger;

    void Log::Init()
    {
        // Set spdlog definition for the way displayed in the console
        // [Time] LoggerName: Message
        spdlog::set_pattern("%^[%T] %n: %v%$");

        // Create and set the core's logger
        s_CoreLogger = spdlog::stdout_color_mt("BELL");
        s_CoreLogger->set_level(spdlog::level::trace);

        // Create and set the app's logger
        s_ClientLogger = spdlog::stdout_color_mt("APP");
        s_ClientLogger->set_level(spdlog::level::trace);
    }
}