#include"pgpch.h"
#include"Camera.h"
#include<glm/gtc/matrix_transform.hpp>
namespace PANGU {
	OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top) :
		ProjectionMatrix(glm::ortho(left, right, bottom, top, -1.0f, 1.0f)),ViewMatrix(glm::mat4x4(1.0f)),
		cameraPos(glm::vec3(0.0f)),rotation(0.0f)
	{
		ViewProjectionMatrix = ProjectionMatrix * ViewMatrix;
	}
	void OrthographicCamera::SetProjection(glm::mat4 projection)
	{
		this->ProjectionMatrix = projection;
		ViewProjectionMatrix = ProjectionMatrix * ViewMatrix;
	}
	void OrthographicCamera::RecalculateViewMatrix()
	{
		// ������ռ䵽����ռ�ı任
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), cameraPos) *
			glm::rotate(glm::mat4(1.0f), glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f));

		//viewMatrix������任����任
		//������任��ԭ��λ�ã�����Ӧ������Ӧ����任
		ViewMatrix = glm::inverse(transform);
		ViewProjectionMatrix = ProjectionMatrix * ViewMatrix;
	}
}