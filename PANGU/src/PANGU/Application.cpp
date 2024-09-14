#include"pgpch.h"
#include "Application.h"
#include"glm/glm.hpp"
#include"Render/RenderCommand.h"
#include"PANGU/Core/TimeStep.h"
#include"PANGU/Events/KeyEvent.h"

namespace PANGU {

	Application* Application::instance = nullptr;

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application::Application(){
		PG_CORE_ASSERT(!instance, "Application 已经存在，然而尝试创建新的Application");

		instance = this;
		window = std::unique_ptr<Window>(Window::Create());
		window->SetEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1));
		window->SetVSync(true);

		Renderer::Init();	//初始化渲染器

		imGuiLayer = new ImGuiLayer();
		PushOverlay(imGuiLayer);	//添加ImGui层
	}
	Application::~Application(){}
	void Application::run() {
		while (Running) {
			float curFrameTime = glfwGetTime();
			TimeStep timeStep(curFrameTime - lastFrameTime);
			lastFrameTime = curFrameTime;

			if (!WindowMinimized) {
				for (Layer* layer : layerStack)
					layer->OnUpdate(timeStep);

				// 每一层都可以利用ImGUI来实现一些额外的窗口
				imGuiLayer->Begin();
				for (Layer* layer : layerStack)
					layer->OnImGuiRenderer();
				imGuiLayer->End();
			}

			window->OnUpdate();
		}
	}

	void Application::OnEvent(Event& e) {
		EventDispatch dispatcher(e);
		//分发事件
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClosed));
		dispatcher.Dispatch<KeyPressedEvent>(BIND_EVENT_FN(Application::OnKeyPressedEvent));
		dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(OnWindowResized));

		//将事件传递给每一层进行处理
		for (auto it = layerStack.end(); it != layerStack.begin();) {
			--it;
			(*it)->OnEvent(e);
			if (e.Handled)
				break;
		}
	}

	void Application::PushLayer(Layer* layer) {
		layerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* overlay) {
		layerStack.PushOverlay(overlay);
		overlay->OnAttach();
	}




	bool Application::OnKeyPressedEvent(KeyPressedEvent& event) {
		switch (event.GetKeyCode())
		{
		case Key::Escape: {Running = false; return true; }
		default: break;
		}
		return false;
	}

	bool Application::OnWindowResized(WindowResizeEvent& event)
	{
		if (event.GetWidth() == 0 || event.GetHeight() == 0) {
			WindowMinimized = true;
			return false;
		}

		WindowMinimized = false;
		Renderer::OnWindowResized(event.GetWidth(), event.GetHeight());

		return false;
	}

	bool Application::OnWindowClosed(WindowCloseEvent& event) {
		Running = false;
		return true;
	}

} 