#include"pgpch.h"
#include"PANGU/Core/Core.h"
#include "OpenGLShader.h"
#include<glad/glad.h>
#include<glm/gtc/type_ptr.hpp>
#include<fstream>
#include<regex>
#include<algorithm>

namespace PANGU {
	static GLenum ConvertFromStringToGLenum(const std::string& str) {

		std::string lowerStr = str;
		std::transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), ::tolower);

		if (lowerStr == "vertex")
			return GL_VERTEX_SHADER;
		else if (lowerStr == "fragment" || lowerStr == "pixel")
			return GL_FRAGMENT_SHADER;
		else if (lowerStr == "geometry")
			return GL_GEOMETRY_SHADER;

		PG_CORE_ERROR("解析shader文件时遇到未知标识符: {0}", str.c_str());
		return 0;
	}

	static std::string ConvertFromGLenumToString(GLenum glenum) {
		switch (glenum)
		{
		case GL_VERTEX_SHADER: {return "vertex shader"; }
		case GL_FRAGMENT_SHADER: {return "fragment shader"; }
		case GL_GEOMETRY_SHADER: {return "geometry shader"; }
		default:
			break;
		}
		PG_CORE_ASSERT(false,"调用ConvertFromGLenumToString时遇到未知的GLenum类型(仅支持GL_VERTEX_SHADER/GL_FRAGMENT_SHADER/GL_GEOMETRY_SHADER)");
		return "";
	}

	OpenGLShader::OpenGLShader(const std::string& name, const std::string& verShaderSrc, const std::string& frgShaderSrc):name(name)
	{
		std::unordered_map<GLenum, std::string> shaders({
			{GL_VERTEX_SHADER,verShaderSrc},
			{GL_FRAGMENT_SHADER,frgShaderSrc}
			});
		Compile(shaders);
	}

	OpenGLShader::OpenGLShader(const std::string& filepath)
	{
		// 1. 读取文件,返回string
		std::string result = ReadFile(filepath);

		// 2. 解析string
		auto sources = ParseFromString(result);

		// 3. 编译shaders
		Compile(sources);

		// 4. 解析shader名字   /.../(\\)Texture.glsl ----> Texture
		size_t lastSplash = filepath.find_last_of("/\\");
		size_t lastDot = filepath.find_last_of(".");
		size_t length = lastDot - lastSplash - 1;
		this->name = filepath.substr(lastSplash == std::string::npos ? 0 : lastSplash + 1, length);
	}

	void OpenGLShader::UploadUniformMat4(const std::string& name, const glm::mat4& matrix)
	{
		auto location = glGetUniformLocation(programId, name.c_str());
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}

	void OpenGLShader::UploadUniformFloat(const std::string& name, const glm::float32& value)
	{
		auto location = glGetUniformLocation(programId, name.c_str());
		glUniform1f(location, value);
	}

	void OpenGLShader::UploadUniformFloat2(const std::string& name, const glm::fvec2& value)
	{
		auto location = glGetUniformLocation(programId, name.c_str());
		glUniform2f(location, value.x, value.y);
	}

	void OpenGLShader::UploadUniformFloat3(const std::string& name, const glm::fvec3& value)
	{
		auto location = glGetUniformLocation(programId, name.c_str());
		glUniform3f(location, value.x, value.y, value.z);
	}

	void OpenGLShader::UploadUniformFloat4(const std::string& name, const glm::fvec4& value)
	{
		auto location = glGetUniformLocation(programId, name.c_str());
		glUniform4f(location, value.x, value.y, value.z, value.w);
	}

	std::string OpenGLShader::ReadFile(const std::string& filepath)
	{
		std::ifstream in(filepath);
		if (!in) {
			PG_CORE_ERROR("打开shader文件失败: {0}", filepath.c_str());
			return "";
		}

		std::stringstream buffer;
		buffer << in.rdbuf();	//将文件内容写入字符串流
		return buffer.str();
	}

	std::unordered_map<GLenum, std::string> OpenGLShader::ParseFromString(const std::string& resources)
	{
		std::unordered_map<GLenum, std::string> result;

		std::regex typeRegex(R"(#type\s+([^\s]+))");
		std::smatch match;

		std::string lastType = "";
		size_t lastPos = 0;
		size_t lastLen = 0;

		std::string resource = resources;
		std::string::const_iterator searchStart(resources.cbegin());
		size_t matchPosition;

		while (std::regex_search(searchStart, resources.cend(), match, typeRegex)) {
			if (!lastType.empty()) {
				// 获取匹配位置相对于原字符串的偏移
				matchPosition = match.position(0) + (searchStart - resources.cbegin());
				result[ConvertFromStringToGLenum(lastType)] = resources.substr(lastPos, matchPosition - lastPos);
			}

			// 更新匹配到的type
			lastType = match[1];
			lastPos = match.position(0) + (searchStart - resources.cbegin()) + match.length(0);
			lastLen = match.length(0);
			searchStart = match.suffix().first;
		}

		if (!lastType.empty()) {
			result[ConvertFromStringToGLenum(lastType)] = resource.substr(lastPos);
		}

		return result;
	}

	void OpenGLShader::Compile(const std::unordered_map<GLenum, std::string>& shaders)
	{
		// 创建program
		programId = glCreateProgram();
		PG_CORE_ASSERT(MAX_SHADERS_NUM >= shaders.size(), "shaders数量暂时不能超过MAX_SHADERS_NUM ");
		std::array<GLenum, MAX_SHADERS_NUM> shaderIDs;

		unsigned int shaderIndex = 0;
		for (auto shader : shaders) {
			// Create an empty vertex shader handle
			unsigned int shaderID = glCreateShader(shader.first);

			// Send the vertex shader source code to GL
			// Note that std::string's .c_str is NULL character terminated.
			const GLchar* source = shader.second.c_str();
			glShaderSource(shaderID, 1, &source, 0);

			// Compile the vertex shader
			glCompileShader(shaderID);

			GLint isCompiled = 0;
			glGetShaderiv(shaderID, GL_COMPILE_STATUS, &isCompiled);
			if (isCompiled == GL_FALSE)
			{
				GLint maxLength = 0;
				glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &maxLength);

				// The maxLength includes the NULL character
				std::vector<GLchar> infoLog(maxLength);
				glGetShaderInfoLog(shaderID, maxLength, &maxLength, &infoLog[0]);

				// We don't need the shader anymore.
				glDeleteShader(shaderID);

				PG_CORE_ERROR("{0}着色器编译失败: {1}" ,ConvertFromGLenumToString(shader.first).c_str(), infoLog.data());
				// Use the infoLog as you see fit.
				PG_CORE_ASSERT(false, "着色器编译失败!");
				// In this simple program, we'll just leave
				return;
			}

			glAttachShader(programId, shaderID);

			shaderIDs[shaderIndex++] = shaderID;
		}

		// Link our program
		glLinkProgram(programId);

		for (auto shaderID : shaderIDs) {
			// Don't leak shaders either.
			glDeleteShader(shaderID);
			// Always detach shaders after a successful link.
			glDetachShader(programId, shaderID);
		}

		// Note the different functions here: glGetProgram* instead of glGetShader*.
		GLint isLinked = 0;
		glGetProgramiv(programId, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(programId, maxLength, &maxLength, &infoLog[0]);

			// We don't need the program anymore.
			glDeleteProgram(programId);

			// Use the infoLog as you see fit.
			PG_CORE_ERROR("着色器链接失败: {0}", infoLog.data());
			// Use the infoLog as you see fit.
			PG_CORE_ASSERT(false, "着色器链接失败!");
			// In this simple program, we'll just leave
			return;
		}
	}

	void OpenGLShader::UnBind()
	{
		glUseProgram(0);
	}

	void OpenGLShader::Bind()
	{
		glUseProgram(programId);
	}
}
