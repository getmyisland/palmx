#pragma once

#include "../MessageSystem/MessageSystemNode.h"
#include "Input.h"
#include "InputMapper.h"

class InputSystem : public MessageSystemNode {
public:
	// Constructor
	InputSystem(MessageSystem* messageSystem) : MessageSystemNode(messageSystem) {};
	// Destructor
	~InputSystem() {};

	void ProcessKeyInput(KeyInput keyboardInput);
	void MapKeyInput(KeyInput::KeyInputType inputType, KeyInput::KeyInputKeycode inputKey);

private:
	// Override void provided by MessageSystemNode
	virtual void onNotify(Message message) override;
};