#pragma once

#include "Petal/Core.h"

namespace ptl
{
	class PTL_API Input
	{
	public:
		inline static bool IsKeyPressed(int32_t keyCode) { return s_Instance->IsKeyPressedImpl(keyCode); }
		inline static bool IsMouseButtonPressed(int32_t button) { return s_Instance->IsMouseButtonPressedImpl(button); }
		inline static float GetMouseX() { return s_Instance->GetMouseXImpl(); }
		inline static float GetMouseY() { return s_Instance->GetMouseYImpl(); }

	protected:
		virtual bool IsKeyPressedImpl(int32_t keyCode) = 0;
		virtual bool IsMouseButtonPressedImpl(int32_t button) = 0;
		virtual float GetMouseXImpl() = 0;
		virtual float GetMouseYImpl() = 0;

	private:
		static Input* s_Instance;
	};
}