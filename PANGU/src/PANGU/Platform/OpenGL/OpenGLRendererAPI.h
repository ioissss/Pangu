#pragma once
#include"PANGU/Render/Renderer.h"

namespace PANGU {
	class OpenGLRendererAPI : public RendererAPI
	{
	public:
		// ͨ�� RendererAPI �̳�
		virtual void Init()override;
		virtual void DrawIndexed(const Ref<VertexArray>& vertexArray) override;
		virtual void SetClearColor(const glm::vec4& clearColor);
		virtual void Clear();
		virtual void OnWindowResized(uint32_t width, uint32_t height) override;
	};
}

