#pragma once

#include "Petal/Core/Core.h"

#include "Petal/Renderer/VertexBuffer.h"
#include "Petal/Renderer/IndexBuffer.h"

namespace ptl
{
	class VertexArray
	{
	public:
		virtual ~VertexArray() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void AddVertexBuffer(const Ref<VertexBuffer> &vertexBuffer) = 0;
		virtual void AddIndexBuffer(const Ref<IndexBuffer> &IndexBuffer) = 0;

		virtual const std::vector<Ref<VertexBuffer>> &
			GetVertexBuffers() const = 0;
		virtual const Ref<IndexBuffer> &GetIndexBuffer() const = 0;

		static Ref<VertexArray> Create();
	};
} // namespace ptl
