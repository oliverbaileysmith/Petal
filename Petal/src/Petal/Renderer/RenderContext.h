#pragma once

namespace ptl
{
	enum class RenderAPI
	{
		OpenGL = 0
	};

	class RenderContext
	{
	public:
		virtual void Init() = 0;
		virtual void SwapBuffers() = 0;
	};
}
