#pragma once
#include"PANGU/Render/GraphicsContext.h"
#include<GLFW/glfw3.h>
//OpenGLContext类是OpenGL的context具体实现

namespace PANGU {
	class OpenGLContext :public GraphicsContext
	{
	public:
		OpenGLContext(GLFWwindow* window);

		// 通过 GraphicsContext 继承
		void Init() override;

		void SwapBuffer() override;
	private:
		GLFWwindow* window;
	};
}

