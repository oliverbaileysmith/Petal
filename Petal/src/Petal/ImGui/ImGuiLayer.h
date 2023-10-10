#pragma once

#include "Petal/Core/Layer.h"

#include "Petal/Events/KeyEvent.h"
#include "Petal/Events/MouseEvent.h"
#include "Petal/Events/WindowEvent.h"

#include <imgui.h>

namespace ptl
{
	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		virtual ~ImGuiLayer();

		virtual void Init() override;
		virtual void ShutDown() override;
		virtual void OnUpdate(Timestep timestep) override;
		virtual void OnEvent(Event &event) override;
		virtual void OnImGuiRender() override;

		void Begin();
		void End();

	private:
		bool OnWindowResizeEvent(WindowResizeEvent &event);
		bool OnKeyPressEvent(KeyPressEvent &event);
		bool OnKeyReleaseEvent(KeyReleaseEvent &event);
		bool OnKeyTypeEvent(KeyTypeEvent &event);
		bool OnMouseButtonPressEvent(MouseButtonPressEvent &event);
		bool OnMouseButtonReleaseEvent(MouseButtonReleaseEvent &event);
		bool OnMouseMoveEvent(MouseMoveEvent &event);
		bool OnMouseScrollEvent(MouseScrollEvent &event);

		ImGuiKey PtlToImGuiKeyCode(KeyCode keyCode);
		ImGuiMouseButton PtlToImGuiMouseButtonCode(MouseButtonCode button);
	};
} // namespace ptl
