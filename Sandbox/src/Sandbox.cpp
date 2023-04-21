#include <Petal.h>

#include <imgui.h>

class ExampleLayer : public ptl::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{
	}

	virtual void OnUpdate() override
	{
	}

	virtual void OnEvent(ptl::Event& event) override
	{
		PTL_TRACE("{0}", event);
	}

	virtual void OnImGuiRender() override
	{
		// TODO: Make this work by statically linking OR by setting ImGui context obtained in Petal DLL

		/*ImGui::Begin("Test");
		ImGui::Text("Hello");
		ImGui::End();*/
	}
};

class Sandbox : public ptl::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}

	~Sandbox()
	{

	}
};

ptl::Application* ptl::CreateApplication()
{
	return new Sandbox();
}