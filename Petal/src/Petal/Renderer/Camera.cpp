#include "ptlpch.h"
#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace ptl
{
	Camera::Camera(float vFOV, float viewportWidth, float viewportHeight, float nearClip, float farClip)
	{
		m_Proj = glm::perspective(glm::radians(vFOV), viewportWidth / viewportHeight, nearClip, farClip);
		m_View = glm::lookAt(m_Position, m_Target, { 0.0f, 1.0f, 0.0f });
		m_ViewProj = m_Proj * m_View;
	}

	void Camera::SetPosition(const glm::vec3& position)
	{
		m_Position = position;
		CalculateViewMatrix();
	}

	const glm::vec3& Camera::GetPosition() const
	{
		return m_Position;
	}

	const glm::mat4& Camera::GetViewProj() const
	{
		return m_ViewProj;
	}
	
	void Camera::CalculateViewMatrix()
	{
		m_View = glm::lookAt(m_Position, m_Target, { 0.0f, 1.0f, 0.0f });
		m_ViewProj = m_Proj * m_View;
	}
}