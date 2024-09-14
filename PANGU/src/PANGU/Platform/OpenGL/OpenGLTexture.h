#pragma once

#include"PANGU/Render/Texture.h"

namespace PANGU {
	class OpenGLTexture2D : public Texture2D
	{
	public:
		OpenGLTexture2D(const std::string& filename);
		~OpenGLTexture2D();

		// Í¨¹ý Texture2D ¼Ì³Ð
		uint32_t GetWidth() override { return width; }

		uint32_t GetHeight() override { return height; }

		void Bind(uint32_t slot = 0) override;

	private:
		uint32_t width, height;
		std::string filepath = "";

		uint32_t renderId;
	};
}

