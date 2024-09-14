#pragma once
#include"Renderer.h"

namespace PANGU {
	class RenderCommand
	{
	public:

		inline static void Init() { renderAPI->Init(); }

		inline static void DrawIndexed(const Ref<VertexArray>& vertexArray) {
			renderAPI->DrawIndexed(vertexArray);
		}

		inline static void OnWindowResized(uint32_t width, uint32_t height) { renderAPI->OnWindowResized(width, height); }

		static void SetClearColor(const glm::vec4& clearColor);
		static void Clear();
	private:
		static RendererAPI* renderAPI;
	};
}
