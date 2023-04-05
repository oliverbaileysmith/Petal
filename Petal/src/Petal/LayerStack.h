#pragma once

#include "Petal/Core.h"
#include "Layer.h"

#include <vector>

namespace ptl
{
	class PTL_API LayerStack
	{
	public:
		LayerStack();
		~LayerStack();

		void PushLayer(Layer* layer);
		void PopLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
		void PopOverlay(Layer* overlay);

		std::vector<Layer*>::iterator begin();
		std::vector<Layer*>::iterator end();
	
	private:
		std::vector<Layer*> m_Layers;
		std::vector<Layer*>::iterator m_LayerInsertPos;
	};
}