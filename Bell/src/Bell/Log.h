#ifndef LOG_H
#define LOG_H

#include <memory>

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace Bell {

	class BELL_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};

}

// Core Log macros
#define BZ_CORE_TRACE(...) ::Bell::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define BZ_CORE_INFO(...)  ::Bell::Log::GetCoreLogger()->info(__VA_ARGS__)
#define BZ_CORE_WARN(...)  ::Bell::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define BZ_CORE_ERROR(...) ::Bell::Log::GetCoreLogger()->error(__VA_ARGS__)
#define BZ_CORE_FATAL(...) ::Bell::Log::GetCoreLogger()->fatal(__VA_ARGS__)

// Client Log macros
#define BZ_TRACE(...) ::Bell::Log::GetClientLogger()->trace(__VA_ARGS__)
#define BZ_INFO(...)  ::Bell::Log::GetClientLogger()->info(__VA_ARGS__)
#define BZ_WARN(...)  ::Bell::Log::GetClientLogger()->warn(__VA_ARGS__)
#define BZ_ERROR(...) ::Bell::Log::GetClientLogger()->error(__VA_ARGS__)
#define BZ_FATAL(...) ::Bell::Log::GetClientLogger()->fatal(__VA_ARGS__)

// Header Guard
#endif