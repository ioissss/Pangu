#include"pgpch.h"
#include "Log.h"
namespace PANGU {
	Ref<spdlog::logger> Log::CoreLogger;
	Ref<spdlog::logger> Log::ClientLogger;

	Ref<spdlog::logger>& Log::GetClientLogger() {
#ifdef PANGU_DEBUG
		if (!ClientLogger) {
			printf("------------------------------ ERROR ------------------------------\n");
			printf("-- ClientLogger��ִ��Log::Init()֮ǰ������\n");
			exit(-1);
		}
#endif // PANGU_DEBUG

		return ClientLogger;
	}
	Ref<spdlog::logger>& Log::GetCoreLogger() {
#ifdef PANGU_DEBUG
		if (!ClientLogger) {
			printf("------------------------------ ERROR ------------------------------\n");
			printf("-- CoreLogger��ִ��Log::Init()֮ǰ������");
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