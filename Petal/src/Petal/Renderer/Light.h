#pragma once

#include <glm/glm.hpp>

namespace ptl
{
	struct DirectionalLight
	{
		glm::vec3 m_Direction;
		glm::vec3 m_Ambient;
		glm::vec3 m_Diffuse;
		glm::vec3 m_Specular;

		DirectionalLight(const glm::vec3& direction, const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular);
	};

	struct PointLight
	{
		glm::vec3 m_Position;

		glm::vec3 m_Ambient;
		glm::vec3 m_Diffuse;
		glm::vec3 m_Specular;

		// Attenuation
		float m_Constant;
		float m_Linear;
		float m_Quadratic;

		PointLight(const glm::vec3& position, const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular,
			float constant, float linear, float quadratic);
	};
}
