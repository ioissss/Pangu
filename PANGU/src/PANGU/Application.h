#pragma once
#include"Core.h"

namespace PANGU {
	class PANGU_API Application
	{
	public:
		Application();
		virtual ~Application();
		void run();
	};

	Application* CreateApplication();
}

