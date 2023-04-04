#pragma once

#include "Petal/Window.h"

#include <GLFW/glfw3.h>

namespace ptl
{
	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowProps& props);
		virtual ~WindowsWindow() override;

		void OnUpdate() override;

		virtual void SetEventCallback(const std::function<void(Event&)> eventCallback) override;
		virtual void SetVSync(bool enabled) override;

		virtual uint32_t GetWidth() const override;
		virtual uint32_t GetHeight() const override;
		virtual bool GetVSync() const override;

	private:
		virtual void Init(const WindowProps& props);
		virtual void ShutDown();

	private:
		GLFWwindow* m_Window;

		struct WindowData
		{
			std::string Title;
			uint32_t Width;
			uint32_t Height;
			bool VSync;
			std::function<void(Event&)> EventCallback;
		};

		WindowData m_Data;
	};
}