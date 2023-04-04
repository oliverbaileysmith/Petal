#pragma once

#include "Petal/Core.h"
#include "Window.h"

#include "Petal/Events/Event.h"
#include "Petal/Events/WindowEvent.h"

namespace ptl
{
	class PTL_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& event);

	private:
		bool OnWindowClose(WindowCloseEvent& event);

	private:
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
	};

	// To be defined in client application
	Application *CreateApplication();
}