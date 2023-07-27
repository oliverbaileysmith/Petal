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
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_Window);
	}
}