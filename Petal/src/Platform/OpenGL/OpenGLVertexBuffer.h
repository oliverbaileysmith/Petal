#pragma once

#include "Petal/Renderer/VertexBuffer.h"

#include <glad/glad.h>

namespace ptl
{
	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(float* vertices, uint32_t size);
		virtual ~OpenGLVertexBuffer() override;
		
		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void SetLayout(const VertexBufferLayout& layout) override;
		virtual const VertexBufferLayout& GetLayout() const override;

		static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type);

	private:
		uint32_t m_ID;
		VertexBufferLayout m_Layout;
	};
}
