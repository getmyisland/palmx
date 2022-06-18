#pragma once

#include <unordered_set>
#include "../MessageSystem/MessageSystemNode.h"

class InputSystem : public MessageSystemNode {
public:
	InputSystem(MessageSystem* messageSystem) : MessageSystemNode(messageSystem) {};
	~InputSystem() {};

	virtual void onNotify(Message message) override;
};