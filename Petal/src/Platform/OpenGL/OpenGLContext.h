#pragma once

#include "Petal/Renderer/RenderContext.h"

struct GLFWwindow;

namespace ptl
{
	class OpenGLContext : public RenderContext
	{
	public:
		OpenGLContext(GLFWwindow *window);

		virtual void Init() override;
		virtual void SwapBuffers() override;

	private:
		GLFWwindow *m_Window;
	};
} // namespace ptl
