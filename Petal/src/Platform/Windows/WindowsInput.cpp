#include "ptlpch.h"
#include "WindowsInput.h"

#include "Petal/Application.h"

#include <GLFW/glfw3.h>

namespace ptl
{
	Input* Input::s_Instance = new WindowsInput();

	bool WindowsInput::IsKeyPressedImpl(KeyCode keyCode)
	{
		GLFWwindow* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		int32_t state = glfwGetKey(window, PtlToGLFWKeyCode(keyCode));
		return (state == GLFW_PRESS || state == GLFW_REPEAT);
	}

	bool WindowsInput::IsMouseButtonPressedImpl(MouseButtonCode button)
	{
		GLFWwindow* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		int32_t state = glfwGetMouseButton(window, PtlToGLFWMouseButtonCode(button));
		return state == GLFW_PRESS;
	}

	float WindowsInput::GetMouseXImpl()
	{
		GLFWwindow* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		double mouseX, mouseY;
		glfwGetCursorPos(window, &mouseX, &mouseY);

		return (float)mouseX;
	}

	float WindowsInput::GetMouseYImpl()
	{
		GLFWwindow* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		double mouseX, mouseY;
		glfwGetCursorPos(window, &mouseX, &mouseY);

		return (float)mouseY;
	}

	int32_t WindowsInput::PtlToGLFWKeyCode(KeyCode keyCode)
	{
		return (int32_t)keyCode;
	}

	int32_t WindowsInput::PtlToGLFWMouseButtonCode(MouseButtonCode button)
	{
		return (int32_t)button;
	}

	KeyCode WindowsInput::GLFWToPtlKeyCode(int32_t keyCode)
	{
		return (KeyCode)keyCode;
	}

	MouseButtonCode WindowsInput::GLFWToPtlMouseButtonCode(int32_t button)
	{
		return (MouseButtonCode)button;
	}
}