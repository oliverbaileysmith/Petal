#pragma once

#ifdef PTL_PLATFORM_WINDOWS

extern ptl::Application *ptl::CreateApplication();

int main(int argc, char** argv)
{
	ptl::Log::Init();

	PTL_CORE_INFO("Initialized Log");

	ptl::Application *app = ptl::CreateApplication();
	app->Run();
	delete app;
}

#endif