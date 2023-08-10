#pragma once

#include "Petal/Core/Core.h"
#include "Petal/Events/Event.h"
#include "Petal/Core/Timestep.h"

namespace ptl
{
	class Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void Init();
		virtual void ShutDown();
		virtual void OnUpdate(Timestep timestep);
		virtual void OnEvent(Event& event);
		virtual void OnImGuiRender();

		const std::string& GetName() const;

	protected:
		std::string m_Name;
	};
}