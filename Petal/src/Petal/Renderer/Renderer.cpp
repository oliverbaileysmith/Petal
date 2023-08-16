#include "ptlpch.h"
#include "Renderer.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace ptl
{
	RendererAPI* Renderer::s_RendererAPI = new OpenGLRendererAPI;
	Renderer::SceneData* Renderer::s_SceneData = new Renderer::SceneData;
	ShaderLibrary* Renderer::s_ShaderLibrary = new ShaderLibrary;

	void Renderer::BeginScene(Camera& camera, const Ref<DirectionalLight>& dirLight, const std::vector<Ref<PointLight>>& pointLights)
	{
		s_SceneData->ViewProj = camera.GetViewProj();
		s_SceneData->CameraPosition = camera.GetPosition();

		s_SceneData->DirLight = dirLight;
		s_SceneData->PointLights = pointLights;
		
		Ref<Shader> phongShader = s_ShaderLibrary->Get("PetalMappedPhong");
		Ref<Shader> lampShader = s_ShaderLibrary->Get("PetalLamp");

		// Scene-wide uniforms (this can be extended to upload to all shaders in use)

		// Camera
		lampShader->Bind();
		lampShader->UploadUniformMat4("u_ViewProj", s_SceneData->ViewProj);

		phongShader->Bind();
		phongShader->UploadUniformMat4("u_ViewProj", s_SceneData->ViewProj);
		phongShader->UploadUniformFloat3("u_CameraPosition", s_SceneData->CameraPosition);

		// Directional light
		phongShader->UploadUniformFloat3("u_DirLight.Direction", s_SceneData->DirLight->Direction);
		phongShader->UploadUniformFloat3("u_DirLight.Ambient", s_SceneData->DirLight->Ambient);
		phongShader->UploadUniformFloat3("u_DirLight.Diffuse", s_SceneData->DirLight->Diffuse);
		phongShader->UploadUniformFloat3("u_DirLight.Specular", s_SceneData->DirLight->Specular);

		// Point lights
		// TODO: put in loop
		phongShader->UploadUniformFloat3("u_PointLight.Position", s_SceneData->PointLights[0]->Position);
		phongShader->UploadUniformFloat3("u_PointLight.Ambient", s_SceneData->PointLights[0]->Ambient);
		phongShader->UploadUniformFloat3("u_PointLight.Diffuse", s_SceneData->PointLights[0]->Diffuse);
		phongShader->UploadUniformFloat3("u_PointLight.Specular", s_SceneData->PointLights[0]->Specular);

		phongShader->UploadUniformFloat("u_PointLight.Constant", s_SceneData->PointLights[0]->Constant);
		phongShader->UploadUniformFloat("u_PointLight.Linear", s_SceneData->PointLights[0]->Linear);
		phongShader->UploadUniformFloat("u_PointLight.Quadratic", s_SceneData->PointLights[0]->Quadratic);
	}

	void Renderer::EndScene()
	{
	}

	void Renderer::OnWindowResize(uint32_t width, uint32_t height)
	{
		SetViewport(width, height);
	}

	void Renderer::Submit(const Ref<VertexArray>& vertexArray, const Ref<Material>& material, const glm::mat4& transform)
	{
		material->Bind();
		Ref<Shader> shader = material->GetShader();
		shader->Bind();

		// Per-object uniforms
		shader->UploadUniformMat4("u_Model", transform);
		glm::mat3 normalMatrix = glm::mat3(glm::transpose(glm::inverse(transform)));

		if (shader->GetName() == "PetalMappedPhong")
			shader->UploadUniformMat3("u_NormalMatrix", normalMatrix);

		vertexArray->Bind();
		DrawIndexed(vertexArray);
	}
}