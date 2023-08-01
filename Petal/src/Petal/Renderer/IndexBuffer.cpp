#include "ptlpch.h"
#include "IndexBuffer.h"

#include "Petal/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLIndexBuffer.h"

namespace ptl
{
	IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t count)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:
				PTL_CORE_ASSERT(false, "RenderAPI::None not supported");
				return nullptr;
			case RendererAPI::API::OpenGL:
				return new OpenGLIndexBuffer(indices, count);
		}
		PTL_CORE_ASSERT(false, "Unknown RenderAPI");
		return nullptr;
	}
}