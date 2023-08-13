#include "ptlpch.h"
#include "Renderer.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace ptl
{
	RendererAPI* Renderer::s_RendererAPI = new OpenGLRendererAPI;
	Renderer::SceneData* Renderer::s_SceneData = new Renderer::SceneData;

	void Renderer::BeginScene(Camera& camera)
	{
		s_SceneData->ViewProj = camera.GetViewProj();
		s_SceneData->CameraPosition = camera.GetPosition();
	}

	void Renderer::EndScene()
	{
	}

	void Renderer::OnWindowResize(uint32_t width, uint32_t height)
	{
		SetViewport(width, height);
	}

	void Renderer::Submit(const Ref<VertexArray>& vertexArray, const Ref<Shader>& shader, const glm::mat4& transform)
	{
		shader->Bind();

		shader->UploadUniformMat4("u_ViewProj", s_SceneData->ViewProj);
		shader->UploadUniformMat4("u_Model", transform);

		if (shader->GetName() == "Phong")
			shader->UploadUniformFloat3("u_CameraPosition", s_SceneData->CameraPosition);

		vertexArray->Bind();
		DrawIndexed(vertexArray);
	}
}