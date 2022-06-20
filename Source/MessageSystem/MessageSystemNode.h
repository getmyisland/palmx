#pragma once

#include "MessageSystem.h"

class MessageSystemNode {
public:
    MessageSystemNode(MessageSystem* messageSystem) {
        this->messageSystem = messageSystem;
        // Automatically adds receiver
        this->messageSystem->AddReceiver(this->GetNotifyFunc());
    }

protected:
    MessageSystem* messageSystem;

    std::function<void(Message)> GetNotifyFunc() {
        auto messageListener = [=](Message message) -> void {
            this->onNotify(message);
        };
        return messageListener;
    }

    // Sends a message to the queue
    void Send(Message message) {
        messageSystem->SendMessageToQueue(message);
    }

    // Virtual void that gets overriden in every class implementing this class
    virtual void onNotify(Message message) {
        OutputDebugStringW(L"You forgot to implement the onNotify().\n");
    }
};