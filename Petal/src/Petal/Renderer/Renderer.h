#pragma once

#include "Petal/Renderer/RenderCommand.h"
#include "Petal/Renderer/RendererAPI.h"

namespace ptl
{
	class Renderer
	{
	public:
		static void BeginScene();
		static void EndScene();

		static void Submit(const std::shared_ptr<VertexArray>& vertexArray);

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	};
}
