#include "pgpch.h"
#include "RenderCommand.h"
#include"PANGU/Platform/OpenGL/OpenGLRendererAPI.h"

namespace PANGU {

	RendererAPI* RenderCommand::renderAPI = new OpenGLRendererAPI;

	void RenderCommand::SetClearColor(const glm::vec4& clearColor)
	{
		renderAPI->SetClearColor(clearColor);
	}

	void RenderCommand::Clear()
	{
		renderAPI->Clear();
	}
}
