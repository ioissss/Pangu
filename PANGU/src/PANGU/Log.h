#pragma once

#include"Core/Core.h"
#include"spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include<sstream>
#include<memory>

namespace PANGU {
	class PANGU_API Log
	{
	public:
		static void Init();
		static Ref<spdlog::logger>& GetCoreLogger();
		static Ref<spdlog::logger>& GetClientLogger();
	private: 
		static Ref<spdlog::logger> CoreLogger;
		static Ref<spdlog::logger> ClientLogger;
	};

#define PG_CORE_ERROR(...) ::PANGU::Log::GetCoreLogger()->error(__VA_ARGS__)
#define PG_CORE_WARN(...)  ::PANGU::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define PG_CORE_INFO(...)  ::PANGU::Log::GetCoreLogger()->info(__VA_ARGS__)
#define PG_CORE_TRACE(...) ::PANGU::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define PG_CORE_FATAL(...) ::PANGU::Log::GetCoreLogger()->critical(__VA_ARGS__)

#define PG_ERROR(...) ::PANGU::Log::GetClientLogger()->error(__VA_ARGS__)
#define PG_WARN(...)  ::PANGU::Log::GetClientLogger()->warn(__VA_ARGS__)
#define PG_INFO(...)  ::PANGU::Log::GetClientLogger()->info(__VA_ARGS__)
#define PG_TRACE(...) ::PANGU::Log::GetClientLogger()->trace(__VA_ARGS__)
#define PG_FATAL(...) ::PANGU::Log::GetClientLogger()->critical(__VA_ARGS__)


}
