#pragma once

#include "Petal/Layer.h"

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
		virtual void OnUpdate() override;
		virtual void OnEvent(Event& event) override;
		virtual void OnImGuiRender() override;

		void Begin();
		void End();
	};
}