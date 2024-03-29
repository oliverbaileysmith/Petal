#pragma once

#include "Petal/Core/Core.h"
#include "ptlpch.h"

namespace ptl
{
	enum class EventType
	{
		None,
		AppTick,
		AppUpdate,
		AppRender,
		WindowClose,
		WindowResize,
		WindowFocus,
		WindowUnfocus,
		WindowMove,
		KeyPress,
		KeyRelease,
		KeyType,
		MouseButtonPress,
		MouseButtonRelease,
		MouseMove,
		MouseScroll
	};

	class Event
	{
		friend class EventDispatcher;

	public:
		Event() = default;
		virtual ~Event() = default;

		virtual EventType GetEventType() const = 0;
		virtual const char *GetName() const = 0;
		virtual std::string ToString() const
		{
			return GetName();
		}

	public:
		bool Handled = false;
	};

	class EventDispatcher
	{
	public:
		EventDispatcher(Event &event) : m_Event(event) {}

		template<typename T> bool Dispatch(std::function<bool(T &)> func)
		{
			if (m_Event.GetEventType() == T::GetStaticType())
			{
				m_Event.Handled = func(*(T *)&m_Event);
				return true;
			}
			return false;
		}

	private:
		Event &m_Event;
	};

	inline std::ostream &operator<<(std::ostream &os, const Event &event)
	{
		return os << event.ToString();
	}
} // namespace ptl
