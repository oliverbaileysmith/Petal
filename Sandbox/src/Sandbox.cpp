#include <Petal.h>

class Sandbox : public ptl::Application
{
public:
	Sandbox()
	{

	}

	~Sandbox()
	{

	}
};

ptl::Application *ptl::CreateApplication()
{
	return new Sandbox();
}