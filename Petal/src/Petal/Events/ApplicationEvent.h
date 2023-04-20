#pragma once

#include "Petal/Events/Event.h"

namespace ptl
{
	class PTL_API AppTickEvent : public Event
	{
	public:
		AppTickEvent() = default;
		~AppTickEvent() = default;

		static EventType GetStaticType() { return EventType::AppTick; }
		virtual EventType GetEventType() const override { return GetStaticType(); }
		virtual const char* GetName() const override { return "AppTickEvent"; }
	};

	class PTL_API AppUpdateEvent : public Event
	{
	public:
		AppUpdateEvent() = default;
		~AppUpdateEvent() = default;

		static EventType GetStaticType() { return EventType::AppUpdate; }
		virtual EventType GetEventType() const override { return GetStaticType(); }
		virtual const char* GetName() const override { return "AppUpdateEvent"; }
	};

	class PTL_API AppRenderEvent : public Event
	{
	public:
		AppRenderEvent() = default;
		~AppRenderEvent() = default;

		static EventType GetStaticType() { return EventType::AppRender; }
		virtual EventType GetEventType() const override { return GetStaticType(); }
		virtual const char* GetName() const override { return "AppRenderEvent"; }
	};
}