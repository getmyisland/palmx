#include "InputSystem.h"
#include <iostream>

// Process the keyboard input and convert the hex code to a keycode
void InputSystem::ProcessKeyboardInput(KeyboardInput keyboardInput) {
	std::string inputString;
	inputString.push_back(keyboardInput.getInputChar());
	inputString.pop_back();

#ifdef _DEBUG
	std::clog << inputString << std::endl;
#endif

	KeyboardInput::KeyboardInputKey keyboardInputKey = KeyboardInput::KeyboardInputKey::KEYCODE_E;

	// Decide which input it is
	

	UseKeyboardInput(keyboardInput.getKeyboardInputType(), keyboardInputKey);
}

// Use a function mapped to this key
void InputSystem::UseKeyboardInput(KeyboardInput::KeyboardInputType inputType, KeyboardInput::KeyboardInputKey inputKey)
{
	// If a key down was pressed
	if (inputType == KeyboardInput::KeyboardInputType::INPUT_KEYBOARD_KEY_DOWN) {

	}
	// If a key was released
	else if (inputType == KeyboardInput::KeyboardInputType::INPUT_KEYBOARD_KEY_UP) {

	}
}

// Provided by MessageSystemNode
// Gets automatically called by calling MessageSystem::Notify()
void InputSystem::onNotify(Message message)
{
	
}