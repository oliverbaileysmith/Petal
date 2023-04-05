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

	void Layer::OnUpdate()
	{
	}

	void Layer::OnEvent(Event& event)
	{
	}

	const std::string& Layer::GetName() const
	{
		return m_Name;
	}
}