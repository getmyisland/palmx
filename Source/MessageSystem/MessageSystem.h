#pragma once

#include <functional>
#include <string>
#include <vector>
#include <queue>
#include <Windows.h>

class Message {
public:
    // Enum holding all Events
    enum MessageEvent {
        KEY_CHAR,
    };

    Message(const MessageEvent event, const std::string eventValue) {
        messageEvent = event;
        messageEventValue = eventValue;
    }

    MessageEvent GetMessageEvent() { return messageEvent; }
    std::string GetEventValue() { return messageEventValue; }

private:
    // Type of event
    MessageEvent messageEvent;

    // Content of event
    std::string messageEventValue;
};

class MessageSystem {
public:
	MessageSystem() {};
	~MessageSystem() {};

    // Adds a receiver to the vector
    void AddReceiver(std::function<void(Message)> messageReceiver) {
        OutputDebugStringW(L"New receiver added.");
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
    std::vector<std::function<void(Message)>> receivers;
    std::queue<Message> messages;
};