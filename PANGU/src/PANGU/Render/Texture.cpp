#include"pgpch.h"
#include"Texture.h"
#include"Renderer.h"
#include"PANGU/Platform/OpenGL/OpenGLTexture.h"

namespace PANGU {
	Texture2D* Texture2D::Create(const std::string& filepath)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: {PG_CORE_ASSERT(false, "调用Texture2D::Create()时，Renderer::GetAPI()获取的结果为None"); }
		case RendererAPI::API::OpenGL: {return new OpenGLTexture2D(filepath); }
		}
		return nullptr;
	}
}