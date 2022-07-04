#pragma once

#include <string>
#include <map>

class SystemEvent {
public:
    // All Events
    enum class Event {
        TEST
    };

    SystemEvent(const Event pEvent) {
        m_Event = pEvent;
    }

    Event getEvent() { return m_Event; }

    std::string getEventString(Event p_Event) {
        std::string strEvent = m_EventMap.find(p_Event)->second;

        if (strEvent.empty()) {
            return "ERROR_EVENT_NOT_FOUND";
        }
        else {
            return strEvent;
        }
    }

private:
    Event m_Event;

    std::map<SystemEvent::Event, std::string> m_EventMap = {
        {SystemEvent::Event::TEST, "TEST"}
    };
};