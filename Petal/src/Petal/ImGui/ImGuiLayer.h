#pragma once

#include "Petal/Layer.h"

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
		float m_Time = 0.0f;
	};
}