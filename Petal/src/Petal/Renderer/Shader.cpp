#include "ptlpch.h"
#include "Shader.h"

#include "Petal/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace ptl
{
	Shader* Shader::Create(const std::string& vertexSource, const std::string& fragmentSource)
	{
		switch (Renderer::GetAPI())
		{
			case RenderAPI::None:
				PTL_CORE_ASSERT(false, "RenderAPI::None not supported");
				return nullptr;
			case RenderAPI::OpenGL:
				return new OpenGLShader(vertexSource, fragmentSource);
		}
		PTL_CORE_ASSERT(false, "Unknown RenderAPI");
		return nullptr;
	}
}