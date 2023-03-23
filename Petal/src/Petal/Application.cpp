#include "Petal/Application.h"

#include "Petal/Events/MouseEvent.h"
#include "Petal/Log.h"

namespace ptl
{
	Application::Application()
	{

	}

	Application::~Application()
	{

	}

	void Application::Run()
	{
		MouseMoveEvent e(500.0f, 500.0f);
		PTL_CORE_INFO(e);

		while (true);
	}
}