#include "ptlpch.h"
#include "Texture.h"

#include "Petal/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLTexture.h"

namespace ptl
{
	Ref<Texture2D> Texture2D::Create(const std::string& filepath)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:
				PTL_CORE_ASSERT(false, "RenderAPI::None not supported");
				return nullptr;
			case RendererAPI::API::OpenGL:
				return std::make_shared<OpenGLTexture2D>(filepath);
		}
		PTL_CORE_ASSERT(false, "Unknown RenderAPI");
		return nullptr;
	}
}