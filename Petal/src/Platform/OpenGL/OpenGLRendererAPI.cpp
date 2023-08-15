#include "ptlpch.h"
#include "OpenGLRendererAPI.h"
#include "Petal/Renderer/Renderer.h"

#include <glad/glad.h>

namespace ptl
{
	void OpenGLRendererAPI::Init()
	{
		glEnable(GL_BLEND);
		glEnable(GL_DEPTH_TEST);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		Renderer::GetShaderLibrary()->Load("../Petal/res/shaders/PetalPhong.glsl");
		Renderer::GetShaderLibrary()->Load("../Petal/res/shaders/PetalMappedPhong.glsl");
		Renderer::GetShaderLibrary()->Load("../Petal/res/shaders/PetalLamp.glsl");
	}

	void OpenGLRendererAPI::SetViewport(uint32_t width, uint32_t height)
	{
		glViewport(0, 0, width, height);
	}

	void OpenGLRendererAPI::SetClearColor(const glm::vec4& color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
	}

	void OpenGLRendererAPI::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void OpenGLRendererAPI::DrawIndexed(const Ref<VertexArray>& vertexArray)
	{
		glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
	}
}
