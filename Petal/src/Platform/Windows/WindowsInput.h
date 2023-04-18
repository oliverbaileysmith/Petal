#pragma once

#include "Petal/Input.h"

namespace ptl
{
	class WindowsInput : public Input
	{
	protected:
		virtual bool IsKeyPressedImpl(int32_t keyCode) override;
		virtual bool IsMouseButtonPressedImpl(int32_t button) override;
		virtual float GetMouseXImpl() override;
		virtual float GetMouseYImpl() override;
	};
}