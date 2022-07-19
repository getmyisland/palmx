#ifndef C_MODULE_EVENT_H
#define C_MODULE_EVENT_H
#ifdef _WIN32
#pragma once
#endif

#include <string>
#include <map>

class C_ModuleEvent
{
public:
	// All Events
	enum class Event
	{
		TEST
	};

	C_ModuleEvent(const Event pEvent)
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

	std::map<C_ModuleEvent::Event, std::string> m_EventMap =
	{
		{C_ModuleEvent::Event::TEST, "TEST"}
	};
};

#endif // C_MODULE_EVENT_H