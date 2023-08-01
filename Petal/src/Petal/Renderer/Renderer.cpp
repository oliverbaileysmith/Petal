#include "ptlpch.h"
#include "Renderer.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace ptl
{
	RendererAPI* Renderer::s_RendererAPI = new OpenGLRendererAPI;

	void Renderer::BeginScene()
	{
	}

	void Renderer::EndScene()
	{
	}

	void Renderer::Submit(const std::shared_ptr<VertexArray>& vertexArray)
	{
		vertexArray->Bind();
		DrawIndexed(vertexArray);
	}
}