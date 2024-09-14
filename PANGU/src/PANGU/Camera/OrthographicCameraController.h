#pragma once
#include"Camera.h"
#include"PANGU/Events/ApplicationEvent.h"
#include"PANGU/Events/MouseEvent.h"
#include"PANGU/Core/KeyCode.h"
#include"PANGU/Core/TimeStep.h"

namespace PANGU {
	class OrthographicCameraController
	{
	public:
		OrthographicCameraController(float aspectRatio, bool rotatable = true);

		void OnUpdate(const TimeStep&);
		void OnEvent(Event& event);
		OrthographicCamera GetCamera() { return m_Camera; }

	private:

		bool OnMouseScrolledEvent(MouseScrolledEvent& event);
		bool OnWindowResizedEvent(WindowResizeEvent& event);

		float m_AspectRatio = 1.0f;
		float m_ZoomLevel = 1.0f;
		float m_RotateSpeed = 20.0f;
		float m_TranslateSpeed = 1.0f;

		glm::vec3 m_CameraPos = { 0.0f,0.0f,0.0f };
		float m_Rotation = 0.0f;

		bool m_Rotatable = true;

		OrthographicCamera m_Camera;
	};
}

