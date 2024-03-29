#pragma once

#include "ptlpch.h"

#include "Petal/Core/Core.h"
#include "Petal/Events/Event.h"
#include "Petal/Renderer/Renderer.h"

namespace ptl
{
	struct WindowProps
	{
		std::string Title;
		uint32_t Width;
		uint32_t Height;

		WindowProps(const std::string &title = "Petal", uint32_t width = 1280,
			uint32_t height = 720)
			: Title(title), Width(width), Height(height)
		{
		}
	};

	class Window
	{
	public:
		Window() = default;
		virtual ~Window() = default;

		virtual void OnUpdate() = 0;

		virtual void SetEventCallback(const std::function<void(Event &)>) = 0;
		virtual void SetVSync(bool enabled) = 0;

		virtual void *GetNativeWindow() const = 0;
		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;
		virtual bool GetVSync() const = 0;
		virtual float GetTime() const = 0;

		static Window *Create(const WindowProps &props = WindowProps());
	};
} // namespace ptl
