#pragma once

#include "Petal/Layer.h"

#include "Petal/Events/KeyEvent.h"
#include "Petal/Events/MouseEvent.h"
#include "Petal/Events/WindowEvent.h"

#include <imgui.h>

namespace ptl
{
	class PTL_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		virtual ~ImGuiLayer();

		virtual void Init() override;
		virtual void ShutDown() override;
		virtual void OnUpdate() override;
		virtual void OnEvent(Event& event) override;

	private:
		bool OnWindowResizeEvent(WindowResizeEvent& event);
		bool OnKeyPressEvent(KeyPressEvent& event);
		bool OnKeyReleaseEvent(KeyReleaseEvent& event);
		bool OnKeyTypeEvent(KeyTypeEvent& event);
		bool OnMouseButtonPressEvent(MouseButtonPressEvent& event);
		bool OnMouseButtonReleaseEvent(MouseButtonReleaseEvent& event);
		bool OnMouseMoveEvent(MouseMoveEvent& event);
		bool OnMouseScrollEvent(MouseScrollEvent& event);

        ImGuiKey GetImGuiKeyCode(int32_t keyCode);

	private:
		float m_Time = 0.0f;
	};
}