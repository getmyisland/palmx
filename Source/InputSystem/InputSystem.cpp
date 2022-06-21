#include "InputSystem.h"
#include <iostream>

// Process the keyboard input and convert the hex code to a keycode
void InputSystem::ProcessKeyInput(KeyInput keyboardInput) {
	std::string inputString;
	inputString.push_back(keyboardInput.getInputChar());
	inputString.pop_back();

#ifdef _DEBUG
	std::clog << inputString << std::endl;
#endif

	KeyInput::KeyInputKey keyboardInputKey = KeyInput::KeyInputKey::KEYCODE_E;

	// Decide which input it is
	

	UseKeyInput(keyboardInput.getKeyInputType(), keyboardInputKey);
}

// Use a function mapped to this key
void InputSystem::UseKeyInput(KeyInput::KeyInputType inputType, KeyInput::KeyInputKey inputKey)
{
	// If a key down was pressed
	if (inputType == KeyInput::KeyInputType::INPUT_KEYBOARD_KEY_DOWN) {

	}
	// If a key was released
	else if (inputType == KeyInput::KeyInputType::INPUT_KEYBOARD_KEY_UP) {

	}
}

// Provided by MessageSystemNode
// Gets automatically called by calling MessageSystem::Notify()
void InputSystem::onNotify(Message message)
{
	
}