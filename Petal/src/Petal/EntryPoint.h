#pragma once

#ifdef PTL_PLATFORM_WINDOWS

extern ptl::Application *ptl::CreateApplication();

int main(int argc, char** argv)
{
	ptl::Log::Init();

	const char *a = "Hello";
	const char *b = ":)";
	PTL_CORE_WARN("Initialized Log!");
	PTL_INFO("{0} {1}", a, b);

	ptl::Application *app = ptl::CreateApplication();
	app->Run();
	delete app;
}

#endif