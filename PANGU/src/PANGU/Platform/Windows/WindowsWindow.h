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

		// Window ����
		void SetEventCallback(const EventCallbackFn& callback)override { data.EventCallback = callback; }
		void SetVSync(bool enabled)override;

		//V-Sync��ָ��ֱͬ����������ֱͬ������OpenGL��ȷ������ʾ��ˢ����ͬ�������ȴ���ʾ��ˢ��ʱ�ٽ���ǰ�󻺳��������Լ���"��Ļ˺��"
		//V-Sync����������OpenGL֡�ʲ�����ʾ��ˢ��������

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
