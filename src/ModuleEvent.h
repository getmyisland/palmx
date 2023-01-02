#ifndef MODULE_EVENT_H
#define MODULE_EVENT_H
#ifdef _WIN32
#pragma once
#endif

#include <string>
#include <map>

class ModuleEvent
{
public:
	// All Events
	enum class Event
	{
		TEST
	};

	ModuleEvent(const Event pEvent)
	{
		m_Event = pEvent;
	}

	Event GetEvent()
	{
		return m_Event;
	}

	std::string GetEventString(Event p_Event)
	{
		std::string strEvent = m_EventMap.find(p_Event)->second;

		if (strEvent.empty())
		{
			return "ERROR_EVENT_NOT_FOUND";
		}
		else
		{
			return strEvent;
		}
	}

private:
	Event m_Event;

	std::map<ModuleEvent::Event, std::string> m_EventMap =
	{
		{ModuleEvent::Event::TEST, "TEST"}
	};
};

#endif // MODULE_EVENT_H