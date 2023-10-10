#pragma once

#include "Petal/Core/Core.h"
#include "Petal/Core/KeyCodes.h"
#include "Petal/Core/MouseButtonCodes.h"

namespace ptl
{
	class Input
	{
	public:
		inline static bool IsKeyPressed(KeyCode keyCode)
		{
			return s_Instance->IsKeyPressedImpl(keyCode);
		}
		inline static bool IsMouseButtonPressed(MouseButtonCode button)
		{
			return s_Instance->IsMouseButtonPressedImpl(button);
		}
		inline static float GetMouseX()
		{
			return s_Instance->GetMouseXImpl();
		}
		inline static float GetMouseY()
		{
			return s_Instance->GetMouseYImpl();
		}

	protected:
		virtual bool IsKeyPressedImpl(KeyCode keyCode) = 0;
		virtual bool IsMouseButtonPressedImpl(MouseButtonCode button) = 0;
		virtual float GetMouseXImpl() = 0;
		virtual float GetMouseYImpl() = 0;

	private:
		static Input *s_Instance;
	};
} // namespace ptl
