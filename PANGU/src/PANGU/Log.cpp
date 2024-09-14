#include"pgpch.h"
#include "Log.h"
namespace PANGU {
	Ref<spdlog::logger> Log::CoreLogger;
	Ref<spdlog::logger> Log::ClientLogger;

	Ref<spdlog::logger>& Log::GetClientLogger() {
#ifdef PANGU_DEBUG
		if (!ClientLogger) {
			printf("------------------------------ ERROR ------------------------------\n");
			printf("-- ClientLogger在执行Log::Init()之前被调用\n");
			exit(-1);
		}
#endif // PANGU_DEBUG

		return ClientLogger;
	}
	Ref<spdlog::logger>& Log::GetCoreLogger() {
#ifdef PANGU_DEBUG
		if (!ClientLogger) {
			printf("------------------------------ ERROR ------------------------------\n");
			printf("-- CoreLogger在执行Log::Init()之前被调用");
			exit(-1);
		}
#endif // PANGU_DEBUG
		return CoreLogger;
	}
	void Log::Init() {
		spdlog::set_pattern("%^[%T] %n: %v%$");

		CoreLogger = spdlog::stdout_color_mt("PANGU");
		CoreLogger->set_level(spdlog::level::trace);

		ClientLogger = spdlog::stdout_color_mt("APP");
		ClientLogger->set_level(spdlog::level::trace);

	}
}