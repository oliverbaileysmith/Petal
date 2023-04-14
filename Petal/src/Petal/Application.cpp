#include "ptlpch.h"
#include "Petal/Application.h"

#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)

namespace ptl
{
	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		PTL_CORE_ASSERT(!s_Instance, "Application already exists")
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));
	}

	Application::~Application()
	{

	}

	void Application::Run()
	{
		while (m_Running)
		{
			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();
			
			m_Window->OnUpdate();
		}
	}

	void Application::OnEvent(Event& event)
	{
		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClose));

		PTL_CORE_TRACE("{0}", event);

		for (std::vector<Layer*>::iterator it = m_LayerStack.end(); it != m_LayerStack.begin(); it)
		{
			(*--it)->OnEvent(event);
			if (event.Handled)
				break;
		}
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->Init();
	}

	void Application::PopLayer(Layer* layer)
	{
		m_LayerStack.PopLayer(layer);
		layer->ShutDown();
	}

	void Application::PushOverlay(Layer* overlay)
	{
		m_LayerStack.PushOverlay(overlay);
		overlay->Init();
	}

	void Application::PopOverlay(Layer* overlay)
	{
		m_LayerStack.PopOverlay(overlay);
		overlay->ShutDown();
	}

	Application& Application::Get()
	{
		return *s_Instance;
	}

	Window& Application::GetWindow()
	{
		return *m_Window;
	}

	bool Application::OnWindowClose(WindowCloseEvent& event)
	{
		m_Running = false;
		return true;
	}
}