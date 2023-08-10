#pragma once

#include "Petal/Events/Event.h"

#include "Petal/Core/KeyCodes.h"

namespace ptl
{
	class KeyEvent : public Event
	{
	protected:
		KeyEvent(const KeyCode keyCode)
			: m_KeyCode(keyCode)
		{
		}
		~KeyEvent() = default;

	public:
		KeyCode GetKeyCode() const { return m_KeyCode; }

	protected:
		KeyCode m_KeyCode;
	};

	class KeyPressEvent : public KeyEvent
	{
	public:
		KeyPressEvent(const KeyCode keyCode, bool isRepeat = false)
			: KeyEvent(keyCode), m_IsRepeat(isRepeat)
		{
		}
		~KeyPressEvent() = default;

		static EventType GetStaticType() { return EventType::KeyPress; }
		virtual EventType GetEventType() const override { return GetStaticType(); }
		virtual const char* GetName() const override { return "KeyPressEvent"; }
		virtual std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyPressEvent: " << m_KeyCode << " (repeat: " << m_IsRepeat << ")";
			return ss.str();
		}
	private:
		bool m_IsRepeat;
	};

	class KeyReleaseEvent : public KeyEvent
	{
	public:
		KeyReleaseEvent(const KeyCode keyCode)
			: KeyEvent(keyCode)
		{
		}
		~KeyReleaseEvent() = default;

		static EventType GetStaticType() { return EventType::KeyRelease; }
		virtual EventType GetEventType() const override { return GetStaticType(); }
		virtual const char* GetName() const override { return "KeyReleaseEvent"; }
		virtual std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyReleaseEvent: " << m_KeyCode;
			return ss.str();
		}
	};

	class KeyTypeEvent : public KeyEvent
	{
	public:
		KeyTypeEvent(const KeyCode keyCode)
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