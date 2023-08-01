#include "ptlpch.h"
#include "VertexArray.h"

#include "Petal/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace ptl
{
	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:
				PTL_CORE_ASSERT(false, "RenderAPI::None not supported");
				return nullptr;
			case RendererAPI::API::OpenGL:
				return new OpenGLVertexArray();
		}
		PTL_CORE_ASSERT(false, "Unknown RenderAPI");
		return nullptr;
	}
}
