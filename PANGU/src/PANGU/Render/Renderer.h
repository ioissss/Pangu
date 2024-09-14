#pragma once
#include"VertexArray.h"
#include<glm/glm.hpp>
#include"Shader.h"
#include"PANGU/Camera/Camera.h"

namespace PANGU {
	// 当前使用的RenderAPI相关，OpenGL / DirectX ... 
	class RendererAPI
	{
	public:
		enum class API{ None = 0, OpenGL = 1 };
		inline static API GetRenderAPI() { return renderAPI; }
		inline static API SetRenderAPI(API renderAPI) { renderAPI = renderAPI; }

		virtual void Init() = 0;
		virtual void DrawIndexed(const Ref<VertexArray>& vertexArray) = 0;
		virtual void SetClearColor(const glm::vec4& clearColor) = 0;
		virtual void Clear() = 0;
		virtual void OnWindowResized(uint32_t width, uint32_t height) = 0;
	private:
		static API renderAPI;
	};

	class Renderer {
	public:

		static void Init();
		static void OnWindowResized(uint32_t width, uint32_t height);

		inline static RendererAPI::API GetAPI() {
			return RendererAPI::GetRenderAPI();
		}
		static void BeginScene(const OrthographicCamera& camera);
		static void EndScene();
		static void Submit(Ref<Shader>&shader, Ref<VertexArray>& vertexArray, const glm::mat4& transform = glm::mat4(1.0f));
		inline static void SetRendererAPI(RendererAPI::API rendererAPI) { RendererAPI::SetRenderAPI(rendererAPI); }
	private:
		struct SceneData
		{
			glm::mat4 ViewProjectionMatrix;
		};
		static SceneData* sceneData;
	};
}