#pragma once
#include"PANGU/Render/Shader.h"
namespace PANGU {
	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& name, const std::string& verShaderSrc, const std::string& frgShaderSrc);
		OpenGLShader(const std::string& filepath);
		// Í¨¹ý Shader ¼Ì³Ð
		void UnBind() override;
		void Bind() override;
		const std::string& GetName()const override { return name; }

		// upLoadFunc
		void UploadUniformMat4(const std::string& name, const glm::mat4& matrix);
		void UploadUniformFloat(const std::string& name, const glm::float32& value);
		void UploadUniformFloat2(const std::string& name, const glm::fvec2& value);
		void UploadUniformFloat3(const std::string& name, const glm::fvec3& value);
		void UploadUniformFloat4(const std::string& name, const glm::fvec4& value);

	private:
		typedef unsigned int GLenum;
		std::string ReadFile(const std::string& filepath);
		std::unordered_map<GLenum, std::string> ParseFromString(const std::string& resources);
		void Compile(const std::unordered_map<GLenum, std::string>& shaders);

		uint32_t programId = 0;
		std::string name = "";
	};
}

