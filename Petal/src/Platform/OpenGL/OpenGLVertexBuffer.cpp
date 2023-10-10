#include "ptlpch.h"
#include "OpenGLVertexBuffer.h"

namespace ptl
{
	OpenGLVertexBuffer::OpenGLVertexBuffer(float *vertices, uint32_t size)
	{
		glCreateBuffers(1, &m_ID);
		glBindBuffer(GL_ARRAY_BUFFER, m_ID);
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
	}

	OpenGLVertexBuffer::~OpenGLVertexBuffer()
	{
		glDeleteBuffers(1, &m_ID);
	}

	void OpenGLVertexBuffer::Bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_ID);
	}

	void OpenGLVertexBuffer::Unbind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void OpenGLVertexBuffer::SetLayout(const VertexBufferLayout &layout)
	{
		m_Layout = layout;
	}

	const VertexBufferLayout &OpenGLVertexBuffer::GetLayout() const
	{
		return m_Layout;
	}
} // namespace ptl
