#include"pgpch.h"
#include"VertexArray.h"
#include"PANGU/Platform/OpenGL/OpenGLVertexArray.h"
#include"Renderer.h"

namespace PANGU {
	VertexArray* VertexArray::Create() {
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::OpenGL: { return new OpenGLVertexArray(); }
		case RendererAPI::API::None: {PG_CORE_ERROR("�ݲ�֧��RendererAPI::None"); PG_CORE_ASSERT(false, "����VertexArrayʱ��Renderer::GetAPI ΪNone"); }
		}
		return nullptr;
	}
}