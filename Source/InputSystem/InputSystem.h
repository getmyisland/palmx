#pragma once

#include <Windows.h>
#include "../MessageSystem/MessageSystemNode.h"
#include "InputMapper.h"

class InputSystem : public MessageSystemNode {
public:
	InputSystem(MessageSystem* messageSystem) : MessageSystemNode(messageSystem) {};
	~InputSystem() {};

	void Init();
	void ShutDown();

private:
	InputMapper inputMapper;

	// Override void provided by MessageSystemNode
	virtual void onNotify(Message message) override;
};