#include "InputSystem.h"
#include <iostream>

// Map input to an action
void InputSystem::ProcessKeyboardInput(InputType inputType, char input)
{
	std::clog << input << std::endl;

	// If a key down was pressed
	if (inputType == InputSystem::InputType::INPUT_KEY_DOWN) {

	}
	// If a key was released
	else if (inputType == InputSystem::InputType::INPUT_KEY_UP) {

	}
}

// Provided by MessageSystemNode
// Gets automatically called by calling MessageSystem::Notify()
void InputSystem::onNotify(Message message)
{
	
}