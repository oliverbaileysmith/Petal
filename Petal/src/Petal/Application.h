#pragma once

#include "Petal/Core.h"

namespace ptl
{
	class PTL_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	// To be defined in client application
	Application *CreateApplication();
}