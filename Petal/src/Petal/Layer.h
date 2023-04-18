#pragma once

#include "Petal/Core.h"
#include "Petal/Events/Event.h"

namespace ptl
{
	class PTL_API Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void Init();
		virtual void ShutDown();
		virtual void OnUpdate();
		virtual void OnEvent(Event& event);

		const std::string& GetName() const;

	protected:
		std::string m_Name;
	};
}