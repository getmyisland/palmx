#pragma once

#include "../MessageSystem/MessageSystemNode.h"
#include "Input.h"

class InputSystem : public MessageSystemNode {
public:
	// Constructor
	InputSystem(MessageSystem* messageSystem) : MessageSystemNode(messageSystem) {};
	// Destructor
	~InputSystem() {};

	void ProcessKeyInput(KeyInput keyboardInput);
	void UseKeyInput(KeyInput::KeyInputType inputType, KeyInput::KeyInputKey inputKey);

private:
	// Override void provided by MessageSystemNode
	virtual void onNotify(Message message) override;
};