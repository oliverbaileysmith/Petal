#include "ptlpch.h"
#include "Shader.h"

#include "Petal/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace ptl
{
	Ref<Shader> Shader::Create(const std::string& filepath)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:
				PTL_CORE_ASSERT(false, "RenderAPI::None not supported");
				return nullptr;
			case RendererAPI::API::OpenGL:
				return std::make_shared<OpenGLShader>(filepath);
		}
		PTL_CORE_ASSERT(false, "Unknown RenderAPI");
		return nullptr;
	}

	Ref<Shader> Shader::Create(const std::string& vertexSource, const std::string& fragmentSource)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:
				PTL_CORE_ASSERT(false, "RenderAPI::None not supported");
				return nullptr;
			case RendererAPI::API::OpenGL:
				return std::make_shared<OpenGLShader>(vertexSource, fragmentSource);
		}
		PTL_CORE_ASSERT(false, "Unknown RenderAPI");
		return nullptr;
	}

	uint32_t Shader::GetSizeOfShaderDataType(ShaderDataType type)
	{
		switch (type)
		{
			case ShaderDataType::Bool: return 1;
			case ShaderDataType::Float: return 4;
			case ShaderDataType::Float2: return 4 * 2;
			case ShaderDataType::Float3: return 4 * 3;
			case ShaderDataType::Float4: return 4 * 4;
			case ShaderDataType::Int: return 4;
			case ShaderDataType::Int2: return 4 * 2;
			case ShaderDataType::Int3: return 4 * 3;
			case ShaderDataType::Int4: return 4 * 4;
			case ShaderDataType::Mat3: return 4 * 3 * 3;
			case ShaderDataType::Mat4: return 4 * 4 * 4;
			case ShaderDataType::None:
			default:
				PTL_CORE_ASSERT(false, "Unknown ShaderDataType");
				return 0;
		}
	}
}