#include"PANGU.h"
#include"PANGU/Core/Core.h"
#include"imgui.h"
#include<glm/gtc/matrix_transform.hpp>

#define PG_BIND_FN(Fn) std::bind(&Fn,this,std::placeholders::_1)
class TestLayer :public PANGU::Layer {
public:
	TestLayer(const std::string& name = "TestLayer"):orthographicCameraController(1280.0f/720.0f){

		shaderLibrary.Load("D:\\CUDA_learningCode\\PANGU\\Sandbox\\src\\assets\\test.glsl");
		cameraPos = glm::vec3(0.0f, 0.0f, 0.0f);

		// draw a triangle
		// Vertex Array
		vertexArray.reset(PANGU::VertexArray::Create());
		texture.reset(PANGU::Texture2D::Create("D:\\container.jpg"));
		//Vertex Buffer

		float vertices[4 * 5] = {
			-0.5f, -0.5f, 0.0f, 0.0f,0.0f,  // ���½�
			0.5f, -0.5f, 0.0f,  1.0f,0.0f,  // ���½�
		   -0.5f,  0.5f, 0.0f, 0.0f,1.0f,  // ���Ͻ�
			0.5f,  0.5f, 0.0f,  1.0f, 1.0f   // ���Ͻ�
		};

		PANGU::Ref<PANGU::VertexBuffer> vertexBuffer(PANGU::VertexBuffer::Create(vertices, sizeof(vertices)));

		//�󶨶������ݵ�GL_ARRAY_BUFFER

		{
			PANGU::BufferLayout layout = {
				{PANGU::ShaderDataType::Float3, "a_Position"},
				{PANGU::ShaderDataType::Float2, "v_TexCord"}
			};
			vertexBuffer->SetLayout(layout);
		}

		vertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[6]{
			0, 1, 2,  // ��һ��������: ���¡����¡�����
			1, 3, 2   // �ڶ���������: ���¡����ϡ�����
		};
		PANGU::Ref<PANGU::IndexBuffer> indexBuffer(PANGU::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		vertexArray->SetIndexBuffer(indexBuffer);

	}

	void OnUpdate(PANGU::TimeStep timeStep) override {
		// update
		orthographicCameraController.OnUpdate(timeStep);

		// RenderCommand��ƽ̨�޹صĳ����࣬�Ծ�̬��ʽ��װ��RenderAPI�ṩ�Ĺ��ܣ�������RenderAPI�����װһ��RenderAPI* ����������ľ���ʵ��
			// ����RenderCommand����װò�Ƹ�����,RerderAPI����һ�������Ľӿ���

		PANGU::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		PANGU::RenderCommand::Clear();

		texture->Bind();
		PANGU::Renderer::BeginScene(orthographicCameraController.GetCamera());	//һЩԤ������
		PANGU::Ref<PANGU::Shader> shader = shaderLibrary.Get("test");
		PANGU::Renderer::Submit(shader, vertexArray);	//�ύvertexArray
		PANGU::Renderer::EndScene();
	}

	void OnImGuiRenderer()override {
		ImGui::Begin("Camera Position");
		ImGui::Text("%f,%f,%f", cameraPos.x, cameraPos.y, cameraPos.z);
		ImGui::End();
	}

	void OnEvent(PANGU::Event& event) override {
		orthographicCameraController.OnEvent(event);
	}
private:
	PANGU::OrthographicCameraController orthographicCameraController;
	PANGU::ShaderLibrary shaderLibrary;
	PANGU::Ref<PANGU::VertexArray> vertexArray;
	PANGU::Ref<PANGU::Texture2D> texture;
	glm::vec3 cameraPos;
	float rotation = 0.0f;
	float moveSpeed = 1.0f;
	float rotateSpeed = 180.0f;
};


class Sandbox :public PANGU::Application {
public:
	Sandbox();
	~Sandbox(){}
};

Sandbox::Sandbox() {
	PushLayer(new TestLayer);
}

PANGU::Application* PANGU::CreateApplication() {
	return new Sandbox();
}