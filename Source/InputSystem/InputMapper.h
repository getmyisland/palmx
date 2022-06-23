#pragma once

#include "Input.h"

class InputMapper {
public:
	InputMapper() {};
	~InputMapper() {};

	// Map keyboard input to function
	void MapKeyboardInput(KeyboardInput::KeyInputType keyboardInputType, KeyboardInput::KeyInputKeycode keyboardInputKeycode);
};