#include "ptlpch.h"
#include "LayerStack.h"

namespace ptl
{
	LayerStack::LayerStack()
	{
	}

	LayerStack::~LayerStack()
	{
		for (Layer* layer : m_Layers)
			delete layer;
	}

	void LayerStack::PushLayer(Layer* layer)
	{
		m_Layers.emplace(m_Layers.begin() + m_LayerInsertPos, layer);
		m_LayerInsertPos++;
		layer->Init();
	}

	void LayerStack::PopLayer(Layer* layer)
	{
		std::vector<Layer*>::iterator it = std::find(m_Layers.begin(), m_Layers.end(), layer);

		if (it != m_Layers.end())
		{
			m_Layers.erase(it);
			m_LayerInsertPos--;
		}
		layer->ShutDown();
	}

	void LayerStack::PushOverlay(Layer* overlay)
	{
		m_Layers.emplace_back(overlay);
		overlay->Init();
	}

	void LayerStack::PopOverlay(Layer* overlay)
	{
		std::vector<Layer*>::iterator it = std::find(m_Layers.begin(), m_Layers.end(), overlay);

		if (it != m_Layers.end())
		{
			m_Layers.erase(it);
		}
		overlay->ShutDown();
	}

	std::vector<Layer*>::iterator LayerStack::begin()
	{
		return m_Layers.begin();
	}

	std::vector<Layer*>::iterator LayerStack::end()
	{
		return m_Layers.end();
	}
}