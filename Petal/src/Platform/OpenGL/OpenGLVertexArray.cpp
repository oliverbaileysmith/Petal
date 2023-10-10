#include "ptlpch.h"
#include "OpenGLVertexArray.h"

#include <glad/glad.h>

#include "Platform/OpenGL/OpenGLShader.h"

namespace ptl
{
	GLenum ShaderDataTypeToOpenGLType(ShaderDataType type)
	{
		switch (type)
		{
		case ShaderDataType::Bool:
			return GL_BOOL;
		case ShaderDataType::Float:
			return GL_FLOAT;
		case ShaderDataType::Float2:
			return GL_FLOAT;
		case ShaderDataType::Float3:
			return GL_FLOAT;
		case ShaderDataType::Float4:
			return GL_FLOAT;
		case ShaderDataType::Int:
			return GL_INT;
		case ShaderDataType::Int2:
			return GL_INT;
		case ShaderDataType::Int3:
			return GL_INT;
		case ShaderDataType::Int4:
			return GL_INT;
		case ShaderDataType::Mat3:
			return GL_FLOAT;
		case ShaderDataType::Mat4:
			return GL_FLOAT;
		case ShaderDataType::None:
		default:
			PTL_CORE_ASSERT(false, "Unknown ShaderDataType");
			return 0;
		}
	}

	OpenGLVertexArray::OpenGLVertexArray()
	{
		glCreateVertexArrays(1, &m_ID);
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		glDeleteVertexArrays(1, &m_ID);
	}

	void OpenGLVertexArray::Bind() const
	{
		glBindVertexArray(m_ID);
	}

	void OpenGLVertexArray::Unbind() const
	{
		glBindVertexArray(0);
	}

	void OpenGLVertexArray::AddVertexBuffer(
		const Ref<VertexBuffer> &vertexBuffer)
	{
		glBindVertexArray(m_ID);
		vertexBuffer->Bind();

		PTL_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(),
			"Vertex buffer has no layout");

		uint32_t index = 0;
		const VertexBufferLayout &layout = vertexBuffer->GetLayout();
		for (const VertexBufferElement &element : layout)
		{
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index, element.GetComponentCount(),
				ShaderDataTypeToOpenGLType(element.Type),
				element.Normalized ? GL_TRUE : GL_FALSE, layout.GetStride(),
				(const void *)element.Offset);
			index++;
		}

		m_VertexBuffers.push_back(vertexBuffer);
	}

	void OpenGLVertexArray::AddIndexBuffer(const Ref<IndexBuffer> &indexBuffer)
	{
		glBindVertexArray(m_ID);
		indexBuffer->Bind();

		m_IndexBuffer = indexBuffer;
	}

	const std::vector<Ref<VertexBuffer>> &
		OpenGLVertexArray::GetVertexBuffers() const
	{
		return m_VertexBuffers;
	}

	const Ref<IndexBuffer> &OpenGLVertexArray::GetIndexBuffer() const
	{
		return m_IndexBuffer;
	}
} // namespace ptl
