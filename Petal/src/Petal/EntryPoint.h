#pragma once

#ifdef PTL_PLATFORM_WINDOWS

extern ptl::Application *ptl::CreateApplication();

int main(int argc, char** argv)
{
	ptl::Application *app = ptl::CreateApplication();
	app->Run();
	delete app;
}

#endif