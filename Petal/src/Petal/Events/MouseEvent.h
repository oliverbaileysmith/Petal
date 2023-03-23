#pragma once

#include "Petal/Events/Event.h"

namespace ptl
{
	class PTL_API MouseButtonEvent : public Event
	{
	protected:
		MouseButtonEvent(const int32_t mouseButton)
			: m_MouseButton(mouseButton)
		{
		}
		~MouseButtonEvent() = default;

	public:
		int32_t GetMouseButton() const { return m_MouseButton; }

	protected:
		int32_t m_MouseButton;
	};

	class PTL_API MouseButtonPressEvent : public MouseButtonEvent
	{
	public:
		MouseButtonPressEvent(const int32_t mouseButton)
			: MouseButtonEvent(mouseButton)
		{
		}
		~MouseButtonPressEvent() = default;

		static EventType GetStaticType() { return EventType::MouseButtonPress; }
		virtual EventType GetEventType() const override { return GetStaticType(); }
		virtual const char *GetName() const override { return "MouseButtonPressEvent"; }
		virtual std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonPressEvent: " << m_MouseButton;
			return ss.str();
		}
	};

	class PTL_API MouseButtonReleaseEvent : public MouseButtonEvent
	{
	public:
		MouseButtonReleaseEvent(const int32_t mouseButton)
			: MouseButtonEvent(mouseButton)
		{
		}
		~MouseButtonReleaseEvent() = default;

		static EventType GetStaticType() { return EventType::MouseButtonRelease; }
		virtual EventType GetEventType() const override { return GetStaticType(); }
		virtual const char *GetName() const override { return "MouseButtonReleaseEvent"; }
		virtual std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonReleaseEvent: " << m_MouseButton;
			return ss.str();
		}
	};

	class PTL_API MouseMoveEvent : public Event
	{
	public:
		MouseMoveEvent(float x, float y)
			: m_X(x), m_Y(y)
		{
		}
		~MouseMoveEvent() = default;

		float GetXPos() const { return m_X; }
		float GetYPos() const { return m_Y; }

		static EventType GetStaticType() { return EventType::MouseMove; }
		virtual EventType GetEventType() const override { return GetStaticType(); }
		virtual const char *GetName() const override { return "MouseMoveEvent"; }
		virtual std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseMoveEvent: " << m_X << ", " << m_Y;
			return ss.str();
		}

	private:
		float m_X;
		float m_Y;
	};

	class PTL_API MouseScrollEvent : public Event
	{
	public:
		MouseScrollEvent(float xOffset, float yOffset)
			: m_XOffset(xOffset), m_YOffset(yOffset)
		{
		}
		~MouseScrollEvent() = default;

		float GetXOffset() const { return m_XOffset; }
		float GetYOffset() const { return m_YOffset; }

		static EventType GetStaticType() { return EventType::MouseScroll; }
		virtual EventType GetEventType() const override { return GetStaticType(); }
		virtual const char *GetName() const override { return "MouseScrollEvent"; }
		virtual std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseScrollEvent: " << m_XOffset << ", " << m_YOffset;
			return ss.str();
		}

	private:
		float m_XOffset;
		float m_YOffset;
	};
}