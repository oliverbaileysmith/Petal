#include "ptlpch.h"
#include "Light.h"

namespace ptl
{
	// Default directional light is top-down magenta for debugging
	DirectionalLight::DirectionalLight()
		: Direction(glm::vec3(0.0f, -1.0f, 0.0f)), Ambient(glm::vec3(1.0f, 0.0f, 1.0f)), Diffuse(glm::vec3(1.0f, 0.0f, 1.0f)), Specular(glm::vec3(1.0f, 0.0f, 1.0f))
	{
	}

	DirectionalLight::DirectionalLight(const glm::vec3& direction, const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular)
		: Direction(direction), Ambient(ambient), Diffuse(diffuse), Specular(specular)
	{
	}

	PointLight::PointLight(const glm::vec3& position, const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular,
		float constant, float linear, float quadratic)
		: Position(position), Ambient(ambient), Diffuse(diffuse), Specular(specular),
		Constant(constant), Linear(linear), Quadratic(quadratic)
	{
	}
}
