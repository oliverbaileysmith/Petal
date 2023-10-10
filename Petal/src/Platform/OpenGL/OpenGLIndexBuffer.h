#pragma once

#include "Petal/Renderer/IndexBuffer.h"

namespace ptl
{
	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(uint32_t *indices, uint32_t count);
		virtual ~OpenGLIndexBuffer() override;

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual uint32_t GetCount() const override;

	private:
		uint32_t m_ID;
		uint32_t m_Count;
	};
} // namespace ptl
