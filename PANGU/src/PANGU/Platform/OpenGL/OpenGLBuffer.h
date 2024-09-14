#pragma once
#include"PANGU/Render/Buffer.h"

namespace PANGU {
	class OpenGLVertexBuffer :public VertexBuffer {
	public:
		OpenGLVertexBuffer(float* vertices,uint32_t size);
		~OpenGLVertexBuffer();
		// 通过 VertexBuffer 继承
		void Bind() const override;
		void UnBind() const override;

		virtual BufferLayout& GetLayout() { return bufferLayout; }
		virtual void SetLayout(const BufferLayout& layout) { bufferLayout = layout; }

	private:
		uint32_t rendererID;
		BufferLayout bufferLayout;
		// 通过 VertexBuffer 继承
	};

	class OpenGLIndexBuffer :public IndexBuffer {
	public:
		OpenGLIndexBuffer(uint32_t* indices,uint32_t count);
		~OpenGLIndexBuffer();

		// 通过 IndexBuffer 继承
		void Bind() const override;
		void UnBind() const override;
		uint32_t GetCount()const override { return count; }
	private:
		uint32_t rendererID;
		uint32_t count;
	};
}
