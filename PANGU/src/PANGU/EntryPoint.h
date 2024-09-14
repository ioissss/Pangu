#pragma once
#ifdef PANGU_PLATFORM_WINDOWS
#include"Application.h"


//实现留给客户端，他们会根据具体需要返回一个Application的子类
extern PANGU::Application* PANGU::CreateApplication();

int main(int argc, char** argv) {
	printf("盘古引擎启动 ...\n");

	//初始化Log
	PANGU::Log::Init();
	PG_CORE_INFO("Log Initialized successfully ...");

	auto app = PANGU::CreateApplication();
	app->run();
	delete app;
}

#endif // PANGU_PLATFORM_WINDOWS
