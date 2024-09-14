#include "pgpch.h"
#include "OpenGLTexture.h"
#include<stb_image.h>
#include<glad/glad.h>

namespace PANGU {

	OpenGLTexture2D::OpenGLTexture2D(const std::string& filename):filepath(filename)
	{
		int width, height, channels;
		stbi_set_flip_vertically_on_load(1);
		stbi_uc* data = stbi_load(filename.c_str(), &width, &height, &channels, 0);
		PG_CORE_ASSERT(data, "加载文件失败:{0}", filename);
		this->width = width;
		this->height = height;

		GLenum textureFormat = 0, Format = 0;
		switch (channels)
		{
		case 3: {textureFormat = GL_RGB8; Format = GL_RGB; break; }
		case 4: {textureFormat = GL_RGBA8; Format = GL_RGBA; break; }
		default:
			break;
		}

		//创建纹理，创建存储
		glCreateTextures(GL_TEXTURE_2D, 1, &renderId);
		glTextureStorage2D(renderId, 1, textureFormat, width, height);

		glTextureParameteri(renderId, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(renderId, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTextureSubImage2D(renderId, 0, 0, 0, width, height, Format, GL_UNSIGNED_BYTE, data);

		stbi_image_free(data);
	}

	OpenGLTexture2D::~OpenGLTexture2D()
	{
		glDeleteTextures(1, &renderId);
	}

	void OpenGLTexture2D::Bind(uint32_t slot)
	{
		glBindTextureUnit(slot, renderId);
	}
}