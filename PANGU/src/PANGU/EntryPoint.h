#pragma once
#ifdef PANGU_PLATFORM_WINDOWS
#include"Application.h"

//ʵ�������ͻ��ˣ����ǻ���ݾ�����Ҫ����һ��Application������
extern PANGU::Application* PANGU::CreateApplication();

int main(int argc, char** argv) {
	printf("�̹����� ...");
	auto app = PANGU::CreateApplication();
	app->run();
	delete app;
}

#endif // PANGU_PLATFORM_WINDOWS
