#include "ptlpch.h"
#include "Material.h"

#include "Petal/Renderer/Renderer.h"

namespace ptl
{

	PhongMaterial::PhongMaterial(const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular, float shininess)
		: m_Ambient(ambient), m_Diffuse(diffuse), m_Specular(specular), m_Shininess(shininess)
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

	MappedPhongMaterial::MappedPhongMaterial(uint32_t ambientDiffuseSlot, const glm::vec3& specular, float shininess)
		: m_AmbientDiffuseSlot(ambientDiffuseSlot), m_Specular(specular), m_Shininess(shininess)
	{
		m_Shader = Renderer::GetShaderLibrary()->Get("PetalMappedPhong");
	}

	void MappedPhongMaterial::Bind() const
	{
		m_Shader->Bind();

		m_Shader->UploadUniformInt("u_Material.AmbientDiffuse", m_AmbientDiffuseSlot);
		m_Shader->UploadUniformFloat3("u_Material.Specular", m_Specular);
		m_Shader->UploadUniformFloat("u_Material.Shininess", m_Shininess);
	}

	const Ref<Shader>& MappedPhongMaterial::GetShader() const
	{
		return m_Shader;
	}

	void MappedPhongMaterial::SetAmbientDiffuseSlot(uint32_t slot)
	{
		m_AmbientDiffuseSlot = slot;
	}

	void MappedPhongMaterial::SetSpecular(const glm::vec3& specular)
	{
		m_Specular = specular;
	}

	void MappedPhongMaterial::SetShininess(float shininess)
	{
		m_Shininess = shininess;
	}
}
