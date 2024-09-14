#include"pgpch.h"
#include "WindowsWindow.h"

namespace PANGU {
	static bool GLFWInitialized = false;

	Window* Window::Create(const WindowProps& props) {
		return new WindowsWindow(props);
	}

	WindowsWindow::~WindowsWindow() {
		Shutdown();
	}

	WindowsWindow::WindowsWindow(const WindowProps& props) {
		Init(props);
	}

	void WindowsWindow::OnUpdate(){
		glfwPollEvents();
		context->SwapBuffer();
	}

	void WindowsWindow::Shutdown() {
		glfwDestroyWindow(window);
	}

	void WindowsWindow::SetVSync(bool Enabled) {

		if (Enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);
		data.VSync = Enabled;
	}

	bool WindowsWindow::IsVSync()const { return data.VSync; }

	void WindowsWindow::Init(const WindowProps& props) {
		data.Title = props.Title;
		data.Height = props.Height;
		data.Width = props.Width;

		PG_CORE_INFO("Create window {0} ({1}, {2})", data.Title, data.Width, data.Height);

		if (!GLFWInitialized) {
			int success = glfwInit();
			PG_CORE_ASSERT(success, "无法初始化 GLFW ！");
			GLFWInitialized = true;
		}

		window = glfwCreateWindow(data.Width, data.Height, data.Title.c_str(), nullptr, nullptr);
		context = new OpenGLContext(window);	//使用OpenGL
		context->Init();

		glfwSetWindowUserPointer(window, &data);
		SetVSync(data.VSync);

		//Set GLFW callback
		glfwSetWindowSizeCallback(window, [](GLFWwindow* window, int width, int height) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			data.Width = width;
			data.Height = height;

			WindowResizeEvent event(width, height);
			data.EventCallback(event);
		});

		glfwSetWindowCloseCallback(window, [](GLFWwindow* window) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			WindowCloseEvent event;
			data.EventCallback(event);
		});

		glfwSetCharCallback(window, [](GLFWwindow* window, unsigned int keycode) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			KeyTypeEvent event(keycode);
			data.EventCallback(event);
		});

		glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			switch (action)
			{
			case GLFW_PRESS: {
				KeyPressedEvent event(key, 0);
				data.EventCallback(event);
				break;
			}
			case GLFW_RELEASE: {
				KeyReleasedEvent event(key);
				data.EventCallback(event);
				break;
			}
			case GLFW_REPEAT: {
				KeyPressedEvent event(key, 1);
				data.EventCallback(event);
				break;
			}
			default:
				break;
			}
		});

		glfwSetMouseButtonCallback(window, [](GLFWwindow* window, int button, int action, int mods)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				switch (action)
				{
				case GLFW_PRESS:
				{
					MouseButtonPressedEvent event(button);
					data.EventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					MouseButtonReleasedEvent event(button);
					data.EventCallback(event);
					break;
				}
				}
			});

		glfwSetScrollCallback(window, [](GLFWwindow* window, double xOffset, double yOffset)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				MouseScrolledEvent event((float)xOffset, (float)yOffset);
				data.EventCallback(event);
			});

		glfwSetCursorPosCallback(window, [](GLFWwindow* window, double xPos, double yPos)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				MouseMovedEvent event((float)xPos, (float)yPos);
				data.EventCallback(event);
			});

	}
}