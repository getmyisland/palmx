#include "InputSystem.h"
#include <iostream>
#include <codecvt>
#include <string>

void InputSystem::Init() {
	
}

void InputSystem::ShutDown() {
	
}

// Process the keyboard input and convert it to a keycode
void InputSystem::ProcessKeyboardInput(KeyboardInput keyboardInput)
{
	// Default initialize keyInputKeycode with null in case it doesn't find the key
	KeyboardInput::KeyInputKeycode keyInputKeycode = KeyboardInput::KeyInputKeycode::KEYCODE_NULL;

	char hexChar[5];
	
	// Create hexadecimal char from the input
	sprintf_s(hexChar, "0x%x", keyboardInput.getInput());

#ifdef _DEBUG
	//std::clog << hexChar << std::endl;
#endif

	// Use the char to search inside the keycode map for a keycode
	auto it = keyboardInput.keycodeInputMap.find(hexChar);

	// If the iterator found a keycode assign it to the keycode variable
	if (it != keyboardInput.keycodeInputMap.end()) {
		keyInputKeycode = it->second;
	}

	// Map the input to a function
	inputMapper.MapKeyboardInput(keyboardInput.getKeyInputType(), keyInputKeycode);
}

// Provided by MessageSystemNode
// Gets automatically called by calling MessageSystem::Notify()
void InputSystem::onNotify(Message message)
{
	
}