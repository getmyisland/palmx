#pragma once

#include "../MessageSystem/MessageSystemNode.h"

class InputSystem : public MessageSystemNode {
public:
	// Constructor
	InputSystem(MessageSystem* messageSystem) : MessageSystemNode(messageSystem) {};
	// Destructor
	~InputSystem() {};

	enum class InputType {
		INPUT_KEY_DOWN,
		INPUT_KEY_UP
	};

	void ProcessKeyboardInput(InputSystem::InputType inputType, char input);

private:
	// Override void provided by MessageSystemNode
	virtual void onNotify(Message message) override;
};