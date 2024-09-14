#include "pgpch.h"
#include "OrthographicCameraController.h"
#include"PANGU/Input.h"
#include<glm/gtc/matrix_transform.hpp>

namespace PANGU {

	OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool rotatable)
		:m_AspectRatio(aspectRatio), m_Camera(-m_ZoomLevel * aspectRatio, m_ZoomLevel* aspectRatio, -m_ZoomLevel, m_ZoomLevel), m_Rotatable(rotatable)
	{

	}

	void OrthographicCameraController::OnEvent(Event& event)
	{
		// 处理事件
		EventDispatch dispatcher(event);
		dispatcher.Dispatch<MouseScrolledEvent>(PG_BIND_FN(OrthographicCameraController::OnMouseScrolledEvent));
		dispatcher.Dispatch<WindowResizeEvent>(PG_BIND_FN(OrthographicCameraController::OnWindowResizedEvent));
	}

	void OrthographicCameraController::OnUpdate(const TimeStep& timeStep)
	{
		if (PANGU::Input::IsKeyPressed(PANGU::Key::A))
			m_CameraPos.x += m_TranslateSpeed * timeStep;
		else if (PANGU::Input::IsKeyPressed(PANGU::Key::D))
			m_CameraPos.x -= m_TranslateSpeed * timeStep;
		if (PANGU::Input::IsKeyPressed(PANGU::Key::W))
			m_CameraPos.y -= m_TranslateSpeed * timeStep;
		else if (PANGU::Input::IsKeyPressed(PANGU::Key::S))
			m_CameraPos.y += m_TranslateSpeed * timeStep;

		if (m_Rotatable) {
			if (PANGU::Input::IsKeyPressed(PANGU::Key::Q))
				m_Rotation -= m_RotateSpeed * timeStep;
			else if (PANGU::Input::IsKeyPressed(PANGU::Key::E))
				m_Rotation += m_RotateSpeed * timeStep;

			m_Camera.SetRotation(m_Rotation);
		}

		m_Camera.SetPosition(m_CameraPos);
	}

	bool OrthographicCameraController::OnMouseScrolledEvent(MouseScrolledEvent& event)
	{
		m_ZoomLevel -= event.GetYOffset() * 0.5f;	//获取滚轮滚动单位
		//m_ZoomLevel = std::max(m_ZoomLevel, 10.0f);
		m_TranslateSpeed = m_ZoomLevel;
		m_Camera.SetProjection(glm::ortho(-m_ZoomLevel * m_AspectRatio, m_ZoomLevel * m_AspectRatio, -m_ZoomLevel, m_ZoomLevel));
		return false;
	}

	bool OrthographicCameraController::OnWindowResizedEvent(WindowResizeEvent& event)
	{
		m_AspectRatio = (float)event.GetWidth() / (float)event.GetHeight();
		m_Camera.SetProjection(glm::ortho(-m_ZoomLevel * m_AspectRatio, m_ZoomLevel * m_AspectRatio, -m_ZoomLevel, m_ZoomLevel));
		return false;
	}
}