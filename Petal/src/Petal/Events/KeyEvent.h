#pragma once

#include "Petal/Events/Event.h"

namespace ptl
{
	class PTL_API KeyEvent : public Event
	{
	protected:
		KeyEvent(const int32_t keyCode)
			: m_KeyCode(keyCode)
		{
		}
		~KeyEvent() = default;

	public:
		int32_t GetKeyCode() const { return m_KeyCode; }

	protected:
		int32_t m_KeyCode;
	};

	class PTL_API KeyPressEvent : public KeyEvent
	{
	public:
		KeyPressEvent(const int32_t keyCode, bool isRepeat = false)
			: KeyEvent(keyCode), m_IsRepeat(isRepeat)
		{
		}
		~KeyPressEvent() = default;

		static EventType GetStaticType() { return EventType::KeyPress; }
		virtual EventType GetEventType() const override { return GetStaticType(); }
		virtual const char *GetName() const override { return "KeyPressEvent"; }
		virtual std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyPressEvent: " << m_KeyCode << " (repeat: " << m_IsRepeat << ")";
			return ss.str();
		}
	private:
		bool m_IsRepeat;
	};

	class PTL_API KeyReleaseEvent : public KeyEvent
	{
	public:
		KeyReleaseEvent(const int32_t keyCode)
			: KeyEvent(keyCode)
		{
		}
		~KeyReleaseEvent() = default;

		static EventType GetStaticType() { return EventType::KeyRelease; }
		virtual EventType GetEventType() const override { return GetStaticType(); }
		virtual const char *GetName() const override { return "KeyReleaseEvent"; }
		virtual std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyReleaseEvent: " << m_KeyCode;
			return ss.str();
		}
	};

	class PTL_API KeyTypeEvent : public KeyEvent
	{
	public:
		KeyTypeEvent(const int32_t keyCode)
			: KeyEvent(keyCode)
		{
		}
		~KeyTypeEvent() = default;

		static EventType GetStaticType() { return EventType::KeyType; }
		virtual EventType GetEventType() const override { return GetStaticType(); }
		virtual const char* GetName() const override { return "KeyTypeEvent"; }
		virtual std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyTypeEvent: " << m_KeyCode;
			return ss.str();
		}
	};
}