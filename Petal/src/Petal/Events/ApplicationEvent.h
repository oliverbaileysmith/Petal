#pragma once

#include "Petal/Events/Event.h"

namespace ptl
{
	class AppTickEvent : public Event
	{
	public:
		AppTickEvent() = default;
		~AppTickEvent() = default;

		static EventType GetStaticType()
		{
			return EventType::AppTick;
		}
		virtual EventType GetEventType() const override
		{
			return GetStaticType();
		}
		virtual const char *GetName() const override
		{
			return "AppTickEvent";
		}
	};

	class AppUpdateEvent : public Event
	{
	public:
		AppUpdateEvent() = default;
		~AppUpdateEvent() = default;

		static EventType GetStaticType()
		{
			return EventType::AppUpdate;
		}
		virtual EventType GetEventType() const override
		{
			return GetStaticType();
		}
		virtual const char *GetName() const override
		{
			return "AppUpdateEvent";
		}
	};

	class AppRenderEvent : public Event
	{
	public:
		AppRenderEvent() = default;
		~AppRenderEvent() = default;

		static EventType GetStaticType()
		{
			return EventType::AppRender;
		}
		virtual EventType GetEventType() const override
		{
			return GetStaticType();
		}
		virtual const char *GetName() const override
		{
			return "AppRenderEvent";
		}
	};
} // namespace ptl
