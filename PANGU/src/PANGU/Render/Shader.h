#pragma once
#include<string>
#include<glm/glm.hpp>
namespace PANGU {
	class Shader
	{
	public:
		Shader(){}

		virtual void UnBind() = 0;
		virtual void Bind() = 0;
		virtual const std::string& GetName()const = 0;

		static Shader* Create(const std::string& name, const std::string& verShaderSrc, const std::string& frgShaderSrc);
		static Shader* Create(const std::string& filepath);
	};

	class ShaderLibrary {
	public:
		ShaderLibrary() = default;

		void Add(const Ref<Shader>& shader);
		void Load(const std::string& filepath);
		void Load(const std::string& name, const std::string& vshaderSrc, const std::string& fshaderSrc);
		Ref<Shader> Get(const std::string& name);
		
	private:
		bool Exist(const std::string& name) { return shaders.find(name) != shaders.end(); }
		std::unordered_map<std::string, Ref<Shader>> shaders;
	};
}

