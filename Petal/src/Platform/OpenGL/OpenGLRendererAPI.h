#pragma once

#include "Petal/Renderer/RendererAPI.h"

namespace ptl
{
	class OpenGLRendererAPI : public RendererAPI
	{
	public:
		virtual void Init() override;
		virtual void SetViewport(uint32_t width, uint32_t height) override;
		virtual void SetClearColor(const glm::vec4& color) override;
		virtual void Clear() override;

		virtual void DrawIndexed(const Ref<VertexArray>& vertexArray) override;
	};
}