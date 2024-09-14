#pragma once

#include"PANGU/Core/Core.h"
#include<string>

namespace PANGU {
	class Texture {
	public:
		Texture() = default;
		virtual ~Texture(){}

		virtual uint32_t GetWidth() = 0;
		virtual uint32_t GetHeight() = 0;
		virtual void Bind(uint32_t slot = 0) = 0;
	};

	class Texture2D :public Texture {
	public:
		virtual ~Texture2D(){}
		static Texture2D* Create(const std::string&);
	};
}