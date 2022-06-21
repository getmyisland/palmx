#pragma once

#include <functional>
#include <string>
#include <vector>
#include <queue>
#include <map>
#include <Windows.h>

class Message {
public:
    // Enum holding all Events
    enum class MessageEvent {
        TEST
    };

    // Constructor
    Message(const MessageEvent event, std::string eventValue) {
        messageEvent = event;
        messageEventValues = eventValue;
    }

    // Getters
    MessageEvent getMessageEvent() { return messageEvent; }
    std::string getEventValue() { return messageEventValues; }
    std::string getEventName(MessageEvent messageEvent) {
        std::string eventName = messageEventMap.find(messageEvent)->second;

        if (eventName.empty()) {
            return "EVENT_NOT_FOUND_ERROR";
        }
        else {
            return eventName;
        }
    }

private:
    // Type of event
    MessageEvent messageEvent;

    // Content of event
    std::string messageEventValues;

    // Debug Map to Output Events as Strings
    std::map<Message::MessageEvent, std::string> messageEventMap = {
        {Message::MessageEvent::TEST, "TEST"}
    };
};

class MessageSystem {
public:
    // Constructor
	MessageSystem() {};
    // Destructor
	~MessageSystem() {};

    // Adds a receiver to the vector
    void AddReceiver(std::function<void(Message)> messageReceiver) {
        receivers.push_back(messageReceiver);
    }

    // Adds a message to the queue
    void SendMessageToQueue(Message message) {
        messages.push(message);
    }

    // Notifies all receivers and goes trough the message queue
    void Notify() {
        while (!messages.empty()) {
            for (auto iter = receivers.begin(); iter != receivers.end(); iter++) {
                (*iter)(messages.front());
            }

            messages.pop();
        }
    }

private:
    // Vector with event receivers
    std::vector<std::function<void(Message)>> receivers;

    // Message Queue
    std::queue<Message> messages;
};