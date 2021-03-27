// Logger Wrapper
// --------------

#ifndef _LOG_H
#define _LOG_H

#include "Bell/Base/Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace Bell 
{
    class Log
    {
    public:
        /**
         * @brief Sets up console logger
         * 
         */
        static void Init(const std::string& coreName = "BELL",  const std::string& appName = "APP");
        static void Shutdown();

        /**
         * @brief Gets the Core Logger which is used for internal messages
         * 
         * @return Ref<spdlog::logger>& 
         */
        inline static Ref<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
        /**
         * @brief Get the Client Logger which is used for external messages
         * 
         * @return Ref<spdlog::logger>& 
         */
        inline static Ref<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

    private:
        /**
         * @brief Core Logger which is used for internal messages
         * 
         */
        static Ref<spdlog::logger> s_CoreLogger;
        /**
         * @brief Client Logger which is used for external messages
         * 
         */
        static Ref<spdlog::logger> s_ClientLogger;
    };

}

// Core Log macros
#define B_CORE_TRACE(...) ::Bell::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define B_CORE_INFO(...)  ::Bell::Log::GetCoreLogger()->info(__VA_ARGS__)
#define B_CORE_WARN(...)  ::Bell::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define B_CORE_ERROR(...) ::Bell::Log::GetCoreLogger()->error(__VA_ARGS__)
#define B_CORE_FATAL(...) ::Bell::Log::GetCoreLogger()->fatal(__VA_ARGS__)

// Client Log macros
#define B_TRACE(...) ::Bell::Log::GetClientLogger()->trace(__VA_ARGS__)
#define B_INFO(...)  ::Bell::Log::GetClientLogger()->info(__VA_ARGS__)
#define B_WARN(...)  ::Bell::Log::GetClientLogger()->warn(__VA_ARGS__)
#define B_ERROR(...) ::Bell::Log::GetClientLogger()->error(__VA_ARGS__)
#define B_FATAL(...) ::Bell::Log::GetClientLogger()->fatal(__VA_ARGS__)

#endif // !_LOG_H