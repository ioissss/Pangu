#pragma once
#include"Core/Core.h"
#include"PANGU/Core/Window.h"
#include"PANGU/Events/ApplicationEvent.h"
#include"PANGU/Events/KeyEvent.h"
#include"LayerStack.h"
#include"Platform/Windows/WindowsInput.h"
#include"ImGui/ImGuiLayer.h"
#include"PANGU/Render/Shader.h"
#include"PANGU/Render/VertexArray.h"
#include"PANGU/Camera/Camera.h"

namespace PANGU {
	class PANGU_API Application
	{
	public:
		Application();
		void OnEvent(Event& e);
		virtual ~Application();
		void run();
		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
		
		static inline Application& Get() {
			PG_CORE_ASSERT(instance, "���Է���һ���յ�Application");
			return *instance;
		}

		Window& GetWindow() {
			PG_CORE_ASSERT(window, "Application�е�windowδ��ʼ���������Ի�ȡ");
			return *window;
		}

	private:
		bool OnWindowResized(WindowResizeEvent& event);
		bool OnWindowClosed(WindowCloseEvent& event);
		bool OnKeyPressedEvent(KeyPressedEvent& event);
	private:
		static Application* instance;
		Scope<Window> window;
		ImGuiLayer* imGuiLayer;
		LayerStack layerStack;
		float lastFrameTime = 0.0f;

		//���Ʊ���
		bool Running = true;
		bool WindowMinimized = false;
	}; 

	Application* CreateApplication();   
}

