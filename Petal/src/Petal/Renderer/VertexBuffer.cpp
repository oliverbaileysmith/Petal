#include "ptlpch.h"
#include "VertexBuffer.h"

#include "Petal/Renderer/Renderer.h"
#include "Petal/Renderer/Shader.h"
#include "Platform/OpenGL/OpenGLVertexBuffer.h"

namespace ptl
{
	// VertexBufferElement

	VertexBufferElement::VertexBufferElement()
	{
	}

	VertexBufferElement::VertexBufferElement(ShaderDataType type, const std::string& name, bool normalized)
		: Name(name), Type(type), Size(Shader::GetSizeOfShaderDataType(type)), Offset(0), Normalized(normalized)
	{
	}

	uint32_t VertexBufferElement::GetComponentCount() const
	{
		switch (Type)
		{
			case ShaderDataType::Bool: return 1;
			case ShaderDataType::Float: return 1;
			case ShaderDataType::Float2: return 2;
			case ShaderDataType::Float3: return 3;
			case ShaderDataType::Float4: return 4;
			case ShaderDataType::Int: return 1;
			case ShaderDataType::Int2: return 2;
			case ShaderDataType::Int3: return 3;
			case ShaderDataType::Int4: return 4;
			case ShaderDataType::Mat3: return 3 * 3;
			case ShaderDataType::Mat4: return 4 * 4;
			case ShaderDataType::None:
			default:
				PTL_CORE_ASSERT(false, "Unknown ShaderDataType");
				return 0;
		}
	}

	// VertexBufferLayout

	VertexBufferLayout::VertexBufferLayout()
	{
	}

	VertexBufferLayout::VertexBufferLayout(const std::vector<VertexBufferElement>& elements)
		: m_Elements(elements), m_Stride(0)
	{
		CalculateOffsetsAndStride();
	}

	uint32_t VertexBufferLayout::GetStride() const
	{
		return m_Stride;
	}

	const std::vector<VertexBufferElement>& VertexBufferLayout::GetElements() const
	{
		return m_Elements;
	}

	std::vector<VertexBufferElement>::iterator VertexBufferLayout::begin()
	{
		return m_Elements.begin();
	}

	std::vector<VertexBufferElement>::iterator VertexBufferLayout::end()
	{
		return m_Elements.end();
	}

	std::vector<VertexBufferElement>::const_iterator VertexBufferLayout::begin() const
	{
		return m_Elements.begin();
	}

	std::vector<VertexBufferElement>::const_iterator VertexBufferLayout::end() const
	{
		return m_Elements.end();
	}

	void VertexBufferLayout::CalculateOffsetsAndStride()
	{
		uint32_t offset = 0;

		for (VertexBufferElement& element : m_Elements)
		{
			element.Offset = offset;
			offset += element.Size;
			m_Stride += element.Size;
		}
	}

	// VertexBuffer

	VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
			case RenderAPI::None:
				PTL_CORE_ASSERT(false, "RenderAPI::None not supported");
				return nullptr;
			case RenderAPI::OpenGL:
				return new OpenGLVertexBuffer(vertices, size);
		}
		PTL_CORE_ASSERT(false, "Unknown RenderAPI");
		return nullptr;
	}
}