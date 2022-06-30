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
        event = pEvent;
    }

    Event getEvent() { return event; }

    std::string getEventName(Event pEvent) {
        std::string eventName = eventMap.find(pEvent)->second;

        if (eventName.empty()) {
            return "EVENT_NOT_FOUND_ERROR";
        }
        else {
            return eventName;
        }
    }

private:
    Event event;

    std::map<SystemEvent::Event, std::string> eventMap = {
        {SystemEvent::Event::TEST, "TEST"}
    };
};