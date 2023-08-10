#pragma once

#include "Petal/Core/Core.h"
#include "Petal/Core/Window.h"

#include "Petal/Core/LayerStack.h"
#include "Petal/ImGui/ImGuiLayer.h"

#include "Petal/Events/Event.h"
#include "Petal/Events/WindowEvent.h"

#include "Petal/Core/Timestep.h"

namespace ptl
{
	class Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& event);

		void PushLayer(Layer* layer);
		void PopLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
		void PopOverlay(Layer* overlay);

		static Application& Get();
		Window& GetWindow();

	private:
		bool OnWindowClose(WindowCloseEvent& event);
		bool OnWindowResize(WindowResizeEvent& event);

	private:
		static Application* s_Instance;
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
		bool m_Minimized = false;
		LayerStack m_LayerStack;
		ImGuiLayer* m_ImGuiLayer;
		float m_LastFrameTime = 0.0f;
	};

	// To be defined in client application
	Application* CreateApplication();
}