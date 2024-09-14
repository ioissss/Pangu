#include"pgpch.h"
#include"Renderer.h"
#include"RenderCommand.h"
#include"PANGU/Platform/OpenGL/OpenGLShader.h"

namespace PANGU {
	Renderer::SceneData* Renderer::sceneData = new Renderer::SceneData();
	RendererAPI::API RendererAPI::renderAPI = RendererAPI::API::OpenGL;

	void Renderer::Init()
	{
		RenderCommand::Init();
	}

	void Renderer::OnWindowResized(uint32_t width, uint32_t height)
	{
		RenderCommand::OnWindowResized(width, height); 
	}

	void Renderer::BeginScene(const OrthographicCamera& camera)
	{
		//TODO
		//添加场景基础信息，如Camera，environment...
		sceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
	}
	void Renderer::EndScene()
	{
	}
	void Renderer::Submit(PANGU::Ref<Shader>& shader, PANGU::Ref<VertexArray>& vertexArray, const glm::mat4& transform)
	{
		shader->Bind();
		vertexArray->Bind();
		auto openGLShader = std::dynamic_pointer_cast<OpenGLShader>(shader);
		openGLShader->UploadUniformMat4("viewProjectionMatrix", sceneData->ViewProjectionMatrix);
		openGLShader->UploadUniformMat4("transform", transform);
		RenderCommand::DrawIndexed(vertexArray);
	}
	//renderAPI先设置为OpenGLAPI
}