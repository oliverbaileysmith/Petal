#include "ptlpch.h"
#include "Light.h"

namespace ptl
{
	DirectionalLight::DirectionalLight(const glm::vec3& direction, const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular)
		: m_Direction(direction), m_Ambient(ambient), m_Diffuse(diffuse), m_Specular(specular)
	{
	}

	PointLight::PointLight(const glm::vec3& position, const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular,
		float constant, float linear, float quadratic)
		: m_Position(position), m_Ambient(ambient), m_Diffuse(diffuse), m_Specular(specular),
		m_Constant(constant), m_Linear(linear), m_Quadratic(quadratic)
	{
	}
}
