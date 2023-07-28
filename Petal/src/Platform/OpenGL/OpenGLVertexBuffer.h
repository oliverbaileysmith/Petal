#pragma once

#include "Petal/Renderer/VertexBuffer.h"

namespace ptl
{
	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(float* vertices, uint32_t size);
		virtual ~OpenGLVertexBuffer() override;
		
		virtual void Bind() const override;
		virtual void Unbind() const override;
	private:
		uint32_t m_ID;
	};
}
