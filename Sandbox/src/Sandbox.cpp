#include <Petal.h>

class ExampleLayer : public ptl::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{
	}

	virtual void OnUpdate() override
	{
		PTL_TRACE("ExampleLayer::OnUpdate");
	}

	virtual void OnEvent(ptl::Event& event) override
	{
		PTL_TRACE("{0}", event);
	}
};

class Sandbox : public ptl::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
		PushOverlay(new ptl::ImGuiLayer());
	}

	~Sandbox()
	{

	}
};

ptl::Application *ptl::CreateApplication()
{
	return new Sandbox();
}