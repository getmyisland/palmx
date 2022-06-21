#include "InputSystem.h"
#include <iostream>

// Process the keyboard input
void InputSystem::ProcessKeyboardInput(KeyboardInput keyboardInput)
{
	std::string inputString;
	inputString.push_back(keyboardInput.getInputChar());
	inputString.pop_back();

#ifdef _DEBUG
	std::clog << inputString << std::endl;
#endif

	// If a key down was pressed
	if (keyboardInput.getKeyboardInputType() == KeyboardInput::KeyboardInputType::INPUT_KEYBOARD_KEY_DOWN) {

	}
	// If a key was released
	else if (keyboardInput.getKeyboardInputType() == KeyboardInput::KeyboardInputType::INPUT_KEYBOARD_KEY_UP) {

	}
}

// Provided by MessageSystemNode
// Gets automatically called by calling MessageSystem::Notify()
void InputSystem::onNotify(Message message)
{
	
}