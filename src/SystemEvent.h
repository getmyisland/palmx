#pragma once

#include <string>
#include <map>

class SystemEvent {
public:
    // Enum holding all Events
    enum class Event {
        TEST
    };

    // Constructor
    SystemEvent(const Event pEvent, std::string pEventValue) {
        event = pEvent;
        eventValue = pEventValue;
    }

    // Getters
    Event getMessageEvent() { return event; }
    std::string getEventValue() { return eventValue; }
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
    // Type of event
    Event event;

    // Content of event
    std::string eventValue;

    // Debug Map to Output Events as Strings
    std::map<SystemEvent::Event, std::string> eventMap = {
        {SystemEvent::Event::TEST, "TEST"}
    };
};