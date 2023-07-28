#include "ptlpch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace ptl
{
	OpenGLContext::OpenGLContext(GLFWwindow* window)
		: m_Window(window)
	{
		PTL_CORE_ASSERT(m_Window, "Window handle is null");
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_Window);

		// Load glad
		int32_t status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		PTL_CORE_ASSERT(status, "Could not initialize glad");

		PTL_CORE_INFO("OpenGL renderer info:");
		PTL_CORE_INFO("  Vendor: {0}", (char*)glGetString(GL_VENDOR));
		PTL_CORE_INFO("  Renderer: {0}", (char*)glGetString(GL_RENDERER));
		PTL_CORE_INFO("  Version: {0}", (char*)glGetString(GL_VERSION));
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_Window);
	}
}