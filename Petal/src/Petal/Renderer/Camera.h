#pragma once

#include <glm/glm.hpp>

namespace ptl
{
	class Camera
	{
	public:
		Camera(float vFOV, float viewportWidth, float viewportHeight, float nearClip, float farClip);

		void SetPosition(const glm::vec3& position);
		void SetEuler(const glm::vec3& euler);
		void Update();

		const glm::vec3& GetPosition() const;
		const glm::vec3& GetEuler() const;
		const glm::vec3& Front() const;
		const glm::vec3& Right() const;
		const glm::vec3& Up() const;

		const glm::mat4& GetViewProj() const;

	private:
		void CalculateViewMatrix();

	private:
		glm::vec3 m_Position = glm::vec3(0.0f, 0.0f, 1.0f);
		glm::vec3 m_Euler = glm::vec3(0.0f); // Pitch, yaw, roll -> x, y, z
		glm::vec3 m_Direction = glm::vec3(1.0f, 0.0f, 0.0f);
		glm::vec3 m_Right = glm::vec3(0.0f, 0.0f, 1.0f);
		glm::vec3 m_Up = glm::vec3(0.0f, 1.0f, 0.0f);

		glm::mat4 m_View = glm::mat4(1.0f);
		glm::mat4 m_Proj = glm::mat4(1.0f);
		glm::mat4 m_ViewProj = glm::mat4(1.0f);

		bool m_Dirty = true; // Requires recalculation of view matrix
	};
}
