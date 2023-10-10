#include "ptlpch.h"
#include "Renderer.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace ptl
{
	RendererAPI *Renderer::s_RendererAPI = new OpenGLRendererAPI;
	Renderer::SceneData *Renderer::s_SceneData = new Renderer::SceneData;
	ShaderLibrary *Renderer::s_ShaderLibrary = new ShaderLibrary;

	void Renderer::BeginScene(Camera &camera,
		const std::vector<Ref<PointLight>> &pointLights,
		const Ref<DirectionalLight> &dirLight)
	{
		s_SceneData->ViewProj = camera.GetViewProj();
		s_SceneData->CameraPosition = camera.GetPosition();

		s_SceneData->PointLights = pointLights;
		if (dirLight)
		{
			s_SceneData->DirLightEnabled = true;
			s_SceneData->DirLight = dirLight;
		}
		else
			s_SceneData->DirLightEnabled = false;

		Ref<Shader> phongShader = s_ShaderLibrary->Get("PetalPhong");
		Ref<Shader> lampShader = s_ShaderLibrary->Get("PetalLamp");

		// Scene-wide uniforms (this can be extended to upload to all shaders in
		// use)

		// Camera
		lampShader->Bind();
		lampShader->UploadUniformMat4("u_ViewProj", s_SceneData->ViewProj);

		phongShader->Bind();
		phongShader->UploadUniformMat4("u_ViewProj", s_SceneData->ViewProj);
		phongShader->UploadUniformFloat3("u_CameraPosition",
			s_SceneData->CameraPosition);

		// Directional light
		phongShader->UploadUniformBool("u_DirLightEnabled",
			s_SceneData->DirLightEnabled);

		if (dirLight)
		{
			phongShader->UploadUniformFloat3("u_DirLight.Direction",
				s_SceneData->DirLight->Direction);
			phongShader->UploadUniformFloat3("u_DirLight.Ambient",
				s_SceneData->DirLight->Ambient);
			phongShader->UploadUniformFloat3("u_DirLight.Diffuse",
				s_SceneData->DirLight->Diffuse);
			phongShader->UploadUniformFloat3("u_DirLight.Specular",
				s_SceneData->DirLight->Specular);
		}

		// Point lights
		uint8_t numLights = s_SceneData->PointLights.size();
		PTL_CORE_ASSERT(numLights < 9,
			"Petal supports at most 8 point lights in a scene");
		phongShader->UploadUniformUint("u_NumPointLights", numLights);

		for (int i = 0; i < numLights; i++)
		{
			std::string uniformPrefix;
			uniformPrefix.append("u_PointLights[");
			uniformPrefix.append(std::to_string(i));
			uniformPrefix.append("].");

			phongShader->UploadUniformFloat3(uniformPrefix + "Position",
				s_SceneData->PointLights[i]->Position);
			phongShader->UploadUniformFloat3(uniformPrefix + "Ambient",
				s_SceneData->PointLights[i]->Ambient);
			phongShader->UploadUniformFloat3(uniformPrefix + "Diffuse",
				s_SceneData->PointLights[i]->Diffuse);
			phongShader->UploadUniformFloat3(uniformPrefix + "Specular",
				s_SceneData->PointLights[i]->Specular);

			phongShader->UploadUniformFloat(uniformPrefix + "Constant",
				s_SceneData->PointLights[i]->Constant);
			phongShader->UploadUniformFloat(uniformPrefix + "Linear",
				s_SceneData->PointLights[i]->Linear);
			phongShader->UploadUniformFloat(uniformPrefix + "Quadratic",
				s_SceneData->PointLights[i]->Quadratic);
		}
	}

	void Renderer::EndScene() {}

	void Renderer::OnWindowResize(uint32_t width, uint32_t height)
	{
		SetViewport(width, height);
	}

	void Renderer::Submit(const Ref<VertexArray> &vertexArray,
		const Ref<Material> &material, const glm::mat4 &transform)
	{
		material->Bind();
		Ref<Shader> shader = material->GetShader();

		// Per-object uniforms
		shader->UploadUniformMat4("u_Model", transform);
		glm::mat3 normalMatrix =
			glm::mat3(glm::transpose(glm::inverse(transform)));

		if (shader->GetName() == "PetalPhong")
			shader->UploadUniformMat3("u_NormalMatrix", normalMatrix);

		vertexArray->Bind();
		DrawIndexed(vertexArray);
	}
} // namespace ptl
