#pragma once

class KeyboardInput {
public:
	enum class KeyboardInputType {
		INPUT_KEYBOARD_KEY_DOWN,
		INPUT_KEYBOARD_KEY_UP
	};

	KeyboardInput(KeyboardInputType type, char input) {
		inputType = type;
		inputChar = input;
	}
	~KeyboardInput() {};

	KeyboardInputType getKeyboardInputType() { return inputType; }
	char getInputChar() { return inputChar; }

private:
	KeyboardInputType inputType;
	char inputChar;
};

class MouseInput {

};