#include "ptlpch.h"
#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace ptl
{
	Camera::Camera(float vFOV, float viewportWidth, float viewportHeight, float nearClip, float farClip)
	{
		m_Proj = glm::perspective(glm::radians(vFOV), viewportWidth / viewportHeight, nearClip, farClip);
		CalculateViewMatrix();
	}

	void Camera::SetPosition(const glm::vec3& position)
	{
		m_Position = position;

		m_Dirty = true;
	}

	void Camera::SetEuler(const glm::vec3& euler)
	{
		m_Euler = euler;
		m_Direction.x = cos(glm::radians(m_Euler.y)) * cos(glm::radians(m_Euler.x));
		m_Direction.y = sin(glm::radians(m_Euler.x));
		m_Direction.z = sin(glm::radians(m_Euler.y)) * cos(glm::radians(m_Euler.x));

		m_Direction = glm::normalize(m_Direction);
		m_Right = glm::cross(m_Direction, { 0.0f, 1.0f, 0.0f });
		m_Up = glm::cross(m_Right, m_Direction);

		m_Dirty = true;
	}

	void Camera::Update()
	{
		if (m_Dirty)
		{
			CalculateViewMatrix();
			m_Dirty = false;
		}
	}

	const glm::vec3& Camera::GetPosition() const
	{
		return m_Position;
	}

	const glm::vec3& Camera::GetEuler() const
	{
		return m_Euler;
	}

	const glm::vec3& Camera::Front() const
	{
		return m_Direction;
	}

	const glm::vec3& Camera::Right() const
	{
		return m_Right;
	}

	const glm::vec3& Camera::Up() const
	{
		return m_Up;
	}

	const glm::mat4& Camera::GetViewProj() const
	{
		return m_ViewProj;
	}
	
	void Camera::CalculateViewMatrix()
	{
		m_View = glm::lookAt(m_Position, m_Position + m_Direction, { 0.0f, 1.0f, 0.0f });
		m_ViewProj = m_Proj * m_View;
	}
}