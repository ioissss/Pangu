#include "pgpch.h"
#include "Shader.h"
#include"PANGU/Render/Renderer.h"
#include<glad/glad.h>
#include<glm/gtc/type_ptr.hpp>
#include"PANGU/Platform/OpenGL/OpenGLShader.h"

namespace PANGU {
	Shader* Shader::Create(const std::string& name, const std::string& verShaderSrc, const std::string& frgShaderSrc)
	{
		switch (RendererAPI::GetRenderAPI())
		{
		case RendererAPI::API::OpenGL: { return new OpenGLShader(name, verShaderSrc, frgShaderSrc); }
		case RendererAPI::API::None: {PG_ASSERT(false, "调用Shader::Create时，RendererAPI为 none！"); }
		}
		return nullptr;
	}

	Shader* Shader::Create(const std::string& filepath) {
		switch (RendererAPI::GetRenderAPI())
		{
		case RendererAPI::API::OpenGL: { return new OpenGLShader(filepath); }
		case RendererAPI::API::None: {PG_ASSERT(false, "调用Shader::Create时，RendererAPI为 none！"); }
		}
		return nullptr;
	}

	void ShaderLibrary::Add(const Ref<Shader>& shader)
	{
		const std::string& name = shader->GetName();
		PG_CORE_ASSERT(this->Exist(name), "Shader 已经存在! ");
		shaders[name] = shader;
	}
	void ShaderLibrary::Load(const std::string& filepath)
	{
		Ref<Shader> shader(Shader::Create(filepath));
		PG_CORE_ASSERT(!Exist(shader->GetName()), (shader->GetName() + "Shader 已经存在 !").c_str());
		shaders[shader->GetName()] = shader;
	}
	void ShaderLibrary::Load(const std::string& name, const std::string& vshaderSrc, const std::string& fshaderSrc)
	{
		Ref<Shader> shader(Shader::Create(name, vshaderSrc, fshaderSrc));
		PG_CORE_ASSERT(!Exist(shader->GetName()), (shader->GetName() + "Shader 已经存在 !").c_str());
		shaders[shader->GetName()] = shader;
	}
	Ref<Shader> ShaderLibrary::Get(const std::string& name)
	{
		PG_CORE_ASSERT((shaders.find(name) != shaders.end()), "Shader 不存在!");
		return shaders[name];
	}
}