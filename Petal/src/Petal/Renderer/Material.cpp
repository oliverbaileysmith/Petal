#include "ptlpch.h"
#include "Material.h"

#include "Petal/Renderer/Renderer.h"

namespace ptl
{
	// PHONG MATERIAL

	PhongMaterial::PhongMaterial(const glm::vec3& ambient, const glm::vec3& diffuse,
		const glm::vec3& specular, float shininess)
		: m_Ambient(ambient), m_Diffuse(diffuse), m_Specular(specular),
		m_Shininess(shininess)
	{
		m_Shader = Renderer::GetShaderLibrary()->Get("PetalPhong");
	}

	void PhongMaterial::Bind() const
	{
		m_Shader->Bind();

		m_Shader->UploadUniformFloat3("u_Material.Ambient", m_Ambient);
		m_Shader->UploadUniformFloat3("u_Material.Diffuse", m_Diffuse);
		m_Shader->UploadUniformFloat3("u_Material.Specular", m_Specular);
		m_Shader->UploadUniformFloat("u_Material.Shininess", m_Shininess);

		m_Shader->UploadUniformBool("u_Material.UsingAmbientDiffuseMap", m_UsingAmbientDiffuseMap);
		m_Shader->UploadUniformBool("u_Material.UsingSpecularMap", m_UsingSpecularMap);

		if (m_UsingAmbientDiffuseMap)
		{ 
			m_AmbientDiffuseMap->Bind(m_AmbientDiffuseSlot);
			m_Shader->UploadUniformInt("u_Material.AmbientDiffuseMap", m_AmbientDiffuseSlot);
		}
		if (m_UsingSpecularMap)
		{
			m_SpecularMap->Bind(m_SpecularSlot);
			m_Shader->UploadUniformInt("u_Material.SpecularMap", m_SpecularSlot);
		}
	}

	const Ref<Shader>& PhongMaterial::GetShader() const
	{
		return m_Shader;
	}

	void PhongMaterial::SetAmbient(const glm::vec3& ambient)
	{
		m_Ambient = ambient;
	}

	void PhongMaterial::SetDiffuse(const glm::vec3& diffuse)
	{
		m_Diffuse = diffuse;
	}

	void PhongMaterial::SetSpecular(const glm::vec3& specular)
	{
		m_Specular = specular;
	}

	void PhongMaterial::SetShininess(float shininess)
	{
		m_Shininess = shininess;
	}

	void PhongMaterial::AddAmbientDiffuseMap(Ref<Texture2D> ambientDiffuseMap, uint32_t slot)
	{
		m_AmbientDiffuseMap = ambientDiffuseMap;
		m_AmbientDiffuseSlot = slot;
	}

	void PhongMaterial::AddSpecularMap(Ref<Texture2D> specularMap, uint32_t slot)
	{
		m_SpecularMap = specularMap;
		m_SpecularSlot = slot;
	}

	void PhongMaterial::EnableAmbientDiffuseMap()
	{
		m_UsingAmbientDiffuseMap = true;
	}

	void PhongMaterial::DisableAmbientDiffuseMap()
	{
		m_UsingAmbientDiffuseMap = false;
	}

	void PhongMaterial::EnableSpecularMap()
	{
		m_UsingSpecularMap = true;
	}

	void PhongMaterial::DisableSpecularMap()
	{
		m_UsingSpecularMap = false;
	}

	// LAMP MATERIAL

	LampMaterial::LampMaterial(const glm::vec3& color)
		: m_Color(color)
	{
		m_Shader = Renderer::GetShaderLibrary()->Get("PetalLamp");
	}

	void LampMaterial::Bind() const
	{
		m_Shader->Bind();

		m_Shader->UploadUniformFloat3("u_LampColor", m_Color);
	}

	const Ref<Shader>& LampMaterial::GetShader() const
	{
		return m_Shader;
	}

	void LampMaterial::SetColor(const glm::vec3& color)
	{
		m_Color = color;
	}
}
