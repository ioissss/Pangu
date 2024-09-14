#include "pgpch.h"
#include "OpenGLContext.h"
#include<GLFW/glfw3.h>
#include<glad/glad.h>

namespace PANGU {
	OpenGLContext::OpenGLContext(GLFWwindow* window):window(window)
	{
		PG_CORE_ASSERT(window, "����OpenGLContext�� GKFWwindow* window δ��ʼ����");
	}

	void PANGU::OpenGLContext::Init()
	{
		glfwMakeContextCurrent(window);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		PG_CORE_INFO("OpenGL��Ϣ��");
		PG_CORE_ASSERT(status, "��ʼ��GLADʧ��!");
		PG_CORE_INFO("OpenGL Vendor: {0}", (const char*)glGetString(GL_VENDOR));
		PG_CORE_INFO("OpenGL Renderer: {0}", (const char*)glGetString(GL_RENDERER));
		PG_CORE_INFO("OpenGL Version: {0}", (const char*)glGetString(GL_VERSION));
	}

	void PANGU::OpenGLContext::SwapBuffer()
	{
		glfwSwapBuffers(window);
	}
}