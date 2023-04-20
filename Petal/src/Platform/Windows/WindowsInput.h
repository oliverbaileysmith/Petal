#pragma once

#include "Petal/Input.h"

namespace ptl
{
	class WindowsInput : public Input
	{
	protected:
		virtual bool IsKeyPressedImpl(KeyCode keyCode) override;
		virtual bool IsMouseButtonPressedImpl(MouseButtonCode button) override;
		virtual float GetMouseXImpl() override;
		virtual float GetMouseYImpl() override;

	public:
		static int32_t PtlToGLFWKeyCode(KeyCode keyCode);
		static int32_t PtlToGLFWMouseButtonCode(MouseButtonCode button);
		static KeyCode GLFWToPtlKeyCode(int32_t keyCode);
		static MouseButtonCode GLFWToPtlMouseButtonCode(int32_t button);
	};
}