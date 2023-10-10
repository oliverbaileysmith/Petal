#pragma once

#include "Petal/Core/Core.h"
#include "Layer.h"

#include <vector>

namespace ptl
{
	class LayerStack
	{
	public:
		LayerStack();
		~LayerStack();

		void PushLayer(Layer *layer);
		void PopLayer(Layer *layer);
		void PushOverlay(Layer *overlay);
		void PopOverlay(Layer *overlay);

		std::vector<Layer *>::iterator begin();
		std::vector<Layer *>::iterator end();

	private:
		std::vector<Layer *> m_Layers;
		uint32_t m_LayerInsertPos = 0;
	};
} // namespace ptl
