#include "pgpch.h"
#include "Buffer.h"
#include"Renderer.h"
#include "PANGU/Platform/OpenGL/OpenGLBuffer.h"

namespace PANGU {

	VertexBuffer::~VertexBuffer()
	{
	}

	VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::OpenGL: { return new OpenGLVertexBuffer(vertices,size); }
		case RendererAPI::API::None: {PG_CORE_ERROR("暂不支持RendererAPI::None"); PG_CORE_ASSERT(false, "Renderer::GetAPI 为None"); }
		}
		return nullptr;
	}




	IndexBuffer::~IndexBuffer()
	{
	}

	IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t count)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::OpenGL: { return new OpenGLIndexBuffer(indices, count); }
		case RendererAPI::API::None: {PG_CORE_ERROR("暂不支持RendererAPI::None"); PG_CORE_ASSERT(false, "Renderer::GetAPI 为None"); }
		}
		return nullptr;
	}
}