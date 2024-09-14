#pragma once
#ifdef PANGU_PLATFORM_WINDOWS
#include"Application.h"


//ʵ�������ͻ��ˣ����ǻ���ݾ�����Ҫ����һ��Application������
extern PANGU::Application* PANGU::CreateApplication();

int main(int argc, char** argv) {
	printf("�̹��������� ...\n");

	//��ʼ��Log
	PANGU::Log::Init();
	PG_CORE_INFO("Log Initialized successfully ...");

	auto app = PANGU::CreateApplication();
	app->run();
	delete app;
}

#endif // PANGU_PLATFORM_WINDOWS
