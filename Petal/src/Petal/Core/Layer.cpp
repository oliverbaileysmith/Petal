#include "ptlpch.h"
#include "Layer.h"

namespace ptl
{
	Layer::Layer(const std::string& name)
		: m_Name(name)
	{
	}

	Layer::~Layer()
	{
	}

	void Layer::Init()
	{
	}

	void Layer::ShutDown()
	{
	}

	void Layer::OnUpdate(Timestep timestep)
	{
	}

	void Layer::OnEvent(Event& event)
	{
	}

	void Layer::OnImGuiRender()
	{
	}

	const std::string& Layer::GetName() const
	{
		return m_Name;
	}
}