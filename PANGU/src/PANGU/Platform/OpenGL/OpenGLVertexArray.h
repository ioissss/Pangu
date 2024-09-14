#pragma once
#include"PANGU/Render/VertexArray.h"

namespace PANGU {
	class OpenGLVertexArray : public VertexArray
	{
	public:
		OpenGLVertexArray();
		~OpenGLVertexArray();
		// Í¨¹ý VertexArray ¼Ì³Ð
		virtual void Bind() const override;
		virtual void UnBind() const override;
		virtual void AddVertexBuffer(Ref<VertexBuffer>&) override;
		virtual void SetIndexBuffer(Ref<IndexBuffer>&) override;

		std::vector<Ref<VertexBuffer>> GetVertexBuffer() override { return vertexBuffers; }
		Ref<IndexBuffer> GetIndexBuffer() override { return indexBuffer; }


	private:
		std::vector<Ref<VertexBuffer>> vertexBuffers;
		Ref<IndexBuffer> indexBuffer;
		uint32_t rendererID = 0;
	};
}

