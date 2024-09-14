#pragma once
#include"PANGU/Log.h"
#include"PANGU/Render/Buffer.h"
#include<memory>

namespace PANGU {
	class VertexArray {
	public:
		VertexArray() {};
		virtual ~VertexArray(){}
		virtual void Bind()const = 0;
		virtual void UnBind()const = 0;

		virtual void AddVertexBuffer(Ref<VertexBuffer>&) = 0;
		virtual void SetIndexBuffer(Ref<IndexBuffer>&) = 0;

		virtual std::vector<Ref<VertexBuffer>> GetVertexBuffer() = 0;
		virtual Ref<IndexBuffer> GetIndexBuffer() = 0;

		static VertexArray* Create();
	};
}