#include "ptlpch.h"
#include "WindowsWindow.h"

namespace ptl
{
	static bool s_GLFWInitialized = false;

	WindowsWindow::WindowsWindow(const WindowProps& props)
	{
		Init(props);
	}

	WindowsWindow::~WindowsWindow()
	{
		ShutDown();
	}

	void WindowsWindow::OnUpdate()
	{
		glfwPollEvents();
		glfwSwapBuffers(m_Window);
	}

	void WindowsWindow::SetEventCallback(const std::function<void(Event&)> eventCallback)
	{
		m_Data.EventCallback = eventCallback;
	}

	void WindowsWindow::SetVSync(bool enabled)
	{
		if (enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		m_Data.VSync = enabled;
	}

	uint32_t WindowsWindow::GetWidth() const
	{
		return m_Data.Width;
	}

	uint32_t WindowsWindow::GetHeight() const
	{
		return m_Data.Height;
	}

	bool WindowsWindow::GetVSync() const
	{
		return m_Data.VSync;
	}

	void WindowsWindow::Init(const WindowProps& props)
	{
		m_Data.Title = props.Title;
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;

		if (!s_GLFWInitialized)
		{
			int32_t success = glfwInit();
			PTL_CORE_ASSERT(success, "Could not initialize GLFW");

			s_GLFWInitialized = true;
		}

		m_Window = glfwCreateWindow(m_Data.Width, m_Data.Height, m_Data.Title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(m_Window);
		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSync(true);
		
		PTL_CORE_INFO("Initialized Window \"{0}\" ({1}x{2})", props.Title, props.Width, props.Height);
	}

	void WindowsWindow::ShutDown()
	{
		glfwDestroyWindow(m_Window);
	}

	Window* Window::Create(const WindowProps& props)
	{
		return new WindowsWindow(props);
	}
}