#include"pgpch.h"
#include"VertexArray.h"
#include"PANGU/Platform/OpenGL/OpenGLVertexArray.h"
#include"Renderer.h"

namespace PANGU {
	VertexArray* VertexArray::Create() {
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::OpenGL: { return new OpenGLVertexArray(); }
		case RendererAPI::API::None: {PG_CORE_ERROR("暂不支持RendererAPI::None"); PG_CORE_ASSERT(false, "创建VertexArray时，Renderer::GetAPI 为None"); }
		}
		return nullptr;
	}
}