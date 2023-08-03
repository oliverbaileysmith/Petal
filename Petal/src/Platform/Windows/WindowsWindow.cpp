#include "ptlpch.h"
#include "WindowsWindow.h"

#include "Platform/Windows/WindowsInput.h"
#include "Platform/OpenGL/OpenGLContext.h"
#include "Petal/Renderer/Renderer.h"

#include "Petal/Events/ApplicationEvent.h"
#include "Petal/Events/WindowEvent.h"
#include "Petal/Events/KeyEvent.h"
#include "Petal/Events/MouseEvent.h"

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
		m_Context->SwapBuffers();
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

	void* WindowsWindow::GetNativeWindow() const
	{
		return m_Window;
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

	float WindowsWindow::GetTime() const
	{
		return glfwGetTime();
	}

	void WindowsWindow::Init(const WindowProps& props)
	{
		m_Data.Title = props.Title;
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;
		m_Data.VSync = false;

		// Initialize GLFW

		if (!s_GLFWInitialized)
		{
			int32_t success = glfwInit();
			PTL_CORE_ASSERT(success, "Could not initialize GLFW");

			s_GLFWInitialized = true;
		}

		glfwSetErrorCallback([](int32_t error, const char* description)
			{
				PTL_CORE_ERROR("GLFW Error {0}: {1}", error, description);
			});

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		m_Window = glfwCreateWindow(m_Data.Width, m_Data.Height, m_Data.Title.c_str(), nullptr, nullptr);
		PTL_CORE_INFO("Initialized window \"{0}\" ({1}x{2})", props.Title, props.Width, props.Height);

		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::OpenGL:
				m_Context = new OpenGLContext(m_Window);
				break;
			
			case RendererAPI::API::None:
			default:
				PTL_CORE_ASSERT(false, "RenderAPI::None not supported");
		}

		m_Context->Init();

		glfwSetWindowUserPointer(m_Window, &m_Data);

		// Set GLFW callbacks

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				WindowCloseEvent event;
				data.EventCallback(event);
			});

		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int32_t width, int32_t height)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				data.Width = width;
				data.Height = height;
				
				WindowResizeEvent event(width, height);
				data.EventCallback(event);
			});

		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int32_t key, int32_t scancode, int32_t action, int32_t mods)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				switch (action)
				{
					case GLFW_PRESS:
					{
						KeyPressEvent event(WindowsInput::GLFWToPtlKeyCode(key), 0);
						data.EventCallback(event);
						break;
					}
					case GLFW_RELEASE:
					{
						KeyReleaseEvent event(WindowsInput::GLFWToPtlKeyCode(key));
						data.EventCallback(event);
						break;
					}
					case GLFW_REPEAT:
					{
						KeyPressEvent event(WindowsInput::GLFWToPtlKeyCode(key), 1);
						data.EventCallback(event);
						break;
					}
				}
			});

		glfwSetCharCallback(m_Window, [](GLFWwindow* window, uint32_t keyCode)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				KeyTypeEvent event(WindowsInput::GLFWToPtlKeyCode(keyCode));
				data.EventCallback(event);
			});

		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int32_t button, int32_t action, int32_t mods)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				switch (action)
				{
					case GLFW_PRESS:
					{
						MouseButtonPressEvent event(WindowsInput::GLFWToPtlMouseButtonCode(button));
						data.EventCallback(event);
						break;
					}
					case GLFW_RELEASE:
					{
						MouseButtonReleaseEvent event(WindowsInput::GLFWToPtlMouseButtonCode(button));
						data.EventCallback(event);
						break;
					}
				}
			});

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				MouseMoveEvent event((float)xPos, (float)yPos);
				data.EventCallback(event);
			});

		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				MouseScrollEvent event((float)xOffset, (float)yOffset);
				data.EventCallback(event);
			});
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