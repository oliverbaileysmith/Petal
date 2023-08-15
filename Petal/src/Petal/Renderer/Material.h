#pragma once

#include "Petal/Core/Core.h"
#include "Petal/Renderer/Shader.h"

namespace ptl
{
	class Material
	{
	public:
		virtual void Bind() const = 0;
		virtual const Ref<Shader>& GetShader() const = 0;
	};

	class PhongMaterial : public Material
	{
	public:
		PhongMaterial(const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular, float shininess);
		virtual void Bind() const override;
		virtual const Ref<Shader>& GetShader() const override;

		void SetAmbient(const glm::vec3& ambient);
		void SetDiffuse(const glm::vec3& diffuse);
		void SetSpecular(const glm::vec3& specular);
		void SetShininess(float shininess);

	private:
		Ref<Shader> m_Shader;
		glm::vec3 m_Ambient;
		glm::vec3 m_Diffuse;
		glm::vec3 m_Specular;
		float m_Shininess;
	};

	class LampMaterial : public Material
	{
	public:
		LampMaterial(const glm::vec3& color);
		virtual void Bind() const override;
		virtual const Ref<Shader>& GetShader() const override;

		void SetColor(const glm::vec3& color);

	private:
		Ref<Shader> m_Shader;
		glm::vec3 m_Color;
	};
}
