#pragma once
#include"PANGU/Core/Window.h"
#include"PANGU/Log.h"
#include"PANGU/Events/KeyEvent.h"
#include"PANGU/Events/MouseEvent.h"
#include"PANGU/Events/ApplicationEvent.h"
#include"PANGU/Render/GraphicsContext.h"
#include"PANGU/Platform/OpenGL/OpenGLContext.h"

namespace PANGU {
	class WindowsWindow:public Window
	{
	public: 
		WindowsWindow(const WindowProps& props);
		virtual ~WindowsWindow();
		void OnUpdate()override;

		uint32_t GetWidth() const override { return data.Width; }
		uint32_t GetHeight() const override { return data.Height; }

		// Window 属性
		void SetEventCallback(const EventCallbackFn& callback)override { data.EventCallback = callback; }
		void SetVSync(bool enabled)override;

		//V-Sync是指垂直同步，开启垂直同步，则OpenGL会确保与显示器刷新率同步，即等待显示器刷新时再交换前后缓冲区，可以减少"屏幕撕裂"
		//V-Sync不开启，则OpenGL帧率不受显示器刷新率限制

		bool IsVSync() const override;

		virtual void* GetNativeWindow() const { return window; }


	private:
		virtual void Init(const WindowProps& props);
		virtual void Shutdown();

	private:
		GLFWwindow* window;
		GraphicsContext* context;
		struct WindowData
		{
			std::string Title = "PANGU Engine";
			uint32_t Width = 1200, Height = 800;
			bool VSync = true;
			EventCallbackFn EventCallback = nullptr;
		};

		WindowData data;
	};
}
