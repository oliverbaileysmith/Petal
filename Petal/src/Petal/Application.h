#pragma once

#include "Petal/Core.h"
#include "Window.h"

namespace ptl
{
	class PTL_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	private:
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
	};

	// To be defined in client application
	Application *CreateApplication();
}