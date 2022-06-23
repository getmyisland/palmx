#pragma once

#include <Windows.h>
#include "../MessageSystem/MessageSystemNode.h"
#include "Input.h"
#include "InputMapper.h"

class InputSystem : public MessageSystemNode {
public:
	// Constructor
	InputSystem(MessageSystem* messageSystem) : MessageSystemNode(messageSystem) {};
	// Destructor
	~InputSystem() {};

	void Init();
	void ShutDown();

	// Process the keyboard input and map it
	void ProcessKeyboardInput(KeyboardInput keyboardInput);

	// Create a input event
	void CreateKeyboardInputEvent(KeyboardInput keyboardInput) { ProcessKeyboardInput(keyboardInput); }

private:
	InputMapper inputMapper;

	// Override void provided by MessageSystemNode
	virtual void onNotify(Message message) override;
};