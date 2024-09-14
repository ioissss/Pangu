#pragma once
#include<glm/glm.hpp>

namespace PANGU {
	class OrthographicCamera {
	public:
		OrthographicCamera(float left, float right, float bottom, float top);

		// 设置相机属性
		void SetPosition(const glm::vec3& position) { cameraPos = position; RecalculateViewMatrix(); }
		void SetRotation(float rotation) { this->rotation = rotation; RecalculateViewMatrix(); }
		void SetProjection(glm::mat4 projection);
		// 获取相机属性
		const glm::vec3& GetPosition()const { return cameraPos; }
		float GetRotation()const { return rotation; }
		inline const glm::mat4x4& GetProjectionMatrix()const { return ProjectionMatrix; }
		inline const glm::mat4x4& GetViewMatrix()const { return ViewMatrix; }
		inline const glm::mat4x4& GetViewProjectionMatrix()const { return ViewProjectionMatrix; }
	
	private:
		void RecalculateViewMatrix();
	private:
		glm::vec3 cameraPos = glm::vec3(0.0f);
		float rotation = 0.0f;	//控制相机绕Z轴旋转的角度

		glm::mat4x4 ViewMatrix;
		glm::mat4x4 ProjectionMatrix;
		glm::mat4x4 ViewProjectionMatrix;
	};
}