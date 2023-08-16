#pragma once

#include <glm/glm.hpp>

namespace ptl
{
	struct DirectionalLight
	{
		glm::vec3 Direction;
		glm::vec3 Ambient;
		glm::vec3 Diffuse;
		glm::vec3 Specular;

		DirectionalLight();
		DirectionalLight(const glm::vec3& direction, const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular);
	};

	struct PointLight
	{
		glm::vec3 Position;

		glm::vec3 Ambient;
		glm::vec3 Diffuse;
		glm::vec3 Specular;

		// Attenuation
		float Constant;
		float Linear;
		float Quadratic;

		PointLight(const glm::vec3& position, const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular,
			float constant, float linear, float quadratic);
	};
}
