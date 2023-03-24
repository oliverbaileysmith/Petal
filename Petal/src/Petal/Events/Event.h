#pragma once

#include "Petal/Core.h"
#include "ptlpch.h"

namespace ptl
{
	enum class EventType
	{
		None,
		AppTick, AppUpdate, AppRender,
		WindowClose, WindowResize, WindowFocus, WindowUnfocus, WindowMove,
		KeyPress, KeyRelease,
		MouseButtonPress, MouseButtonRelease, MouseMove, MouseScroll
	};
	
	class PTL_API Event
	{
		friend class EventDispatcher;
	
	public:
		Event() = default;
		virtual ~Event() = default;
		
		virtual EventType GetEventType() const = 0;
		virtual const char *GetName() const = 0;
		virtual std::string ToString() const { return GetName(); }

	protected:
		bool m_Handled = false;
	};

	class EventDispatcher
	{
	public:
		EventDispatcher(Event &event)
			: m_Event(event)
		{
		}

		template<typename T>
		bool Dispatch(std::function<bool(T &)> func)
		{
			if (m_Event.GetEventType() == T::GetStaticType())
			{
				m_Event.m_Handled = func(*(T *)&m_Event);
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
}