#pragma once

#include "Petal/Events/Event.h"

namespace ptl
{
	class PTL_API WindowCloseEvent : public Event
	{
	public:
		WindowCloseEvent() = default;
		~WindowCloseEvent() = default;

		static EventType GetStaticType() { return EventType::WindowClose; }
		virtual EventType GetEventType() const override { return GetStaticType(); }
		virtual const char *GetName() const override { return "WindowCloseEvent"; }
	};

	class PTL_API WindowResizeEvent : public Event
	{
	public:
		WindowResizeEvent(uint32_t width, uint32_t height)
			: m_Width(width), m_Height(height)
		{
		}
		~WindowResizeEvent() = default;

		uint32_t GetWidth() const { return m_Width; }
		uint32_t GetHeight() const { return m_Height; }

		static EventType GetStaticType() { return EventType::WindowResize; }
		virtual EventType GetEventType() const override { return GetStaticType(); }
		virtual const char *GetName() const override { return "WindowResizeEvent"; }
		virtual std::string ToString() const override
		{
			std::stringstream ss;
			ss << "WindowResizeEvent: " << m_Width << ", " << m_Height;
			return ss.str();
		}

	private:
		uint32_t m_Width;
		uint32_t m_Height;
	};

	class PTL_API WindowFocusEvent : public Event
	{
	public:
		WindowFocusEvent() = default;
		~WindowFocusEvent() = default;

		static EventType GetStaticType() { return EventType::WindowFocus; }
		virtual EventType GetEventType() const override { return GetStaticType(); }
		virtual const char *GetName() const override { return "WindowFocusEvent"; }
	};

	class PTL_API WindowUnfocusEvent : public Event
	{
	public:
		WindowUnfocusEvent() = default;
		~WindowUnfocusEvent() = default;

		static EventType GetStaticType() { return EventType::WindowUnfocus; }
		virtual EventType GetEventType() const override { return GetStaticType(); }
		virtual const char *GetName() const override { return "WindowUnfocusEvent"; }
	};

	class PTL_API WindowMoveEvent : public Event
	{
	public:
		WindowMoveEvent(uint32_t x, uint32_t y)
			: m_X(x), m_Y(y)
		{
		}
		~WindowMoveEvent() = default;

		uint32_t GetXPos() const { return m_X; }
		uint32_t GetYPos() const { return m_Y; }

		static EventType GetStaticType() { return EventType::WindowMove; }
		virtual EventType GetEventType() const override { return GetStaticType(); }
		virtual const char *GetName() const override { return "WindowMoveEvent"; }
		virtual std::string ToString() const override
		{
			std::stringstream ss;
			ss << "WindowMoveEvent: " << m_X << ", " << m_Y;
			return ss.str();
		}

	private:
		uint32_t m_X;
		uint32_t m_Y;
	};
}