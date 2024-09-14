#pragma once
#include"PANGU/Render/GraphicsContext.h"
#include<GLFW/glfw3.h>
//OpenGLContext����OpenGL��context����ʵ��

namespace PANGU {
	class OpenGLContext :public GraphicsContext
	{
	public:
		OpenGLContext(GLFWwindow* window);

		// ͨ�� GraphicsContext �̳�
		void Init() override;

		void SwapBuffer() override;
	private:
		GLFWwindow* window;
	};
}

