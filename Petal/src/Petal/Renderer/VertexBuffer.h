#pragma once

#include <vector>

#include "Petal/Renderer/Shader.h"

namespace ptl
{
	struct VertexBufferElement
	{
		std::string Name;
		ShaderDataType Type;
		uint32_t Size;
		uint32_t Offset;
		bool Normalized;

		VertexBufferElement();
		VertexBufferElement(ShaderDataType type, const std::string& name, bool normalized = false);

		uint32_t GetComponentCount() const;
	};

	class VertexBufferLayout
	{
	public:
		VertexBufferLayout();
		VertexBufferLayout(const std::vector<VertexBufferElement>& elements);

		uint32_t GetStride() const;
		const std::vector<VertexBufferElement>& GetElements() const;

		std::vector<VertexBufferElement>::iterator begin();
		std::vector<VertexBufferElement>::iterator end();
		std::vector<VertexBufferElement>::const_iterator begin() const;
		std::vector<VertexBufferElement>::const_iterator end() const;

	private:
		void CalculateOffsetsAndStride();

	private:
		std::vector<VertexBufferElement> m_Elements;
		uint32_t m_Stride;
	};

	class VertexBuffer
	{
	public:
		virtual ~VertexBuffer() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;
		
		virtual void SetLayout(const VertexBufferLayout& layout) = 0;
		virtual const VertexBufferLayout& GetLayout() const = 0;

		static VertexBuffer* Create(float* vertices, uint32_t size);
	};
}
