#include "InputSystem.h"
#include <iostream>

// Process the keyboard input and convert the hex code to a keycode
void InputSystem::ProcessKeyInput(KeyInput keyboardInput) {
	std::string inputString = "W";
	
	// Check if size is bigger than 1
	if (inputString.size() > 1) {
		// Remove last character from string
		inputString.resize(inputString.size() - 1);
	}

#ifdef _DEBUG
	std::clog << inputString << std::endl;
#endif

	// Decide which input it is
	KeyInput::KeyInputKeycode keyboardInputKeycode = KeyInput::KeyInputKeycode::KEYCODE_NULL;
	
	// ERROR here InputString is an empty string
	auto iterator = keyboardInput.keycodeInputMap.find(inputString);

	if (iterator != keyboardInput.keycodeInputMap.end()) {
		keyboardInputKeycode = iterator->second;
	}

	MapKeyInput(keyboardInput.getKeyInputType(), keyboardInputKeycode);
}

// Use a function mapped to this key
void InputSystem::MapKeyInput(KeyInput::KeyInputType inputType, KeyInput::KeyInputKeycode inputKeycode)
{
	switch (inputKeycode) {
	case KeyInput::KeyInputKeycode::KEYCODE_LEFT_MOUSE:
		break;
	case KeyInput::KeyInputKeycode::KEYCODE_RIGHT_MOUSE:
		break;
	case KeyInput::KeyInputKeycode::KEYCODE_CONTROL_BREAK_PROCESSING:
		break;
	case KeyInput::KeyInputKeycode::KEYCODE_MIDDLE_MOUSE:
		break;
	case KeyInput::KeyInputKeycode::KEYCODE_BACKSPACE:
		break;
	case KeyInput::KeyInputKeycode::KEYCODE_TAB:
		std::clog << "You opened the scoreboard!" << std::endl;

		break;
	case KeyInput::KeyInputKeycode::KEYCODE_RETURN:
		break;
	case KeyInput::KeyInputKeycode::KEYCODE_SHIFT:
		std::clog << "You are running!" << std::endl;

		break;
	case KeyInput::KeyInputKeycode::KEYCODE_CONTROL:
		break;
	case KeyInput::KeyInputKeycode::KEYCODE_ALT:
		break;
	case KeyInput::KeyInputKeycode::KEYCODE_PAUSE:
		break;
	case KeyInput::KeyInputKeycode::KEYCODE_CAPITAL:
		break;
	case KeyInput::KeyInputKeycode::KEYCODE_ESCAPE:
		break;
	case KeyInput::KeyInputKeycode::KEYCODE_SPACE:
		break;
	case KeyInput::KeyInputKeycode::KEYCODE_ARROW_LEFT:
		break;
	case KeyInput::KeyInputKeycode::KEYCODE_ARROW_UP:
		break;
	case KeyInput::KeyInputKeycode::KEYCODE_ARROW_RIGHT:
		break;
	case KeyInput::KeyInputKeycode::KEYCODE_ARROW_DOWN:
		break;
	case KeyInput::KeyInputKeycode::KEYCODE_0:
		break;
	case KeyInput::KeyInputKeycode::KEYCODE_1:
		break;
	case KeyInput::KeyInputKeycode::KEYCODE_2:
		break;
	case KeyInput::KeyInputKeycode::KEYCODE_3:
		break;
	case KeyInput::KeyInputKeycode::KEYCODE_4:
		break;
	case KeyInput::KeyInputKeycode::KEYCODE_5:
		break;
	case KeyInput::KeyInputKeycode::KEYCODE_6:
		break;
	case KeyInput::KeyInputKeycode::KEYCODE_7:
		break;
	case KeyInput::KeyInputKeycode::KEYCODE_8:
		break;
	case KeyInput::KeyInputKeycode::KEYCODE_9:
		break;
	case KeyInput::KeyInputKeycode::KEYCODE_A:
		break;
	case KeyInput::KeyInputKeycode::KEYCODE_B:
		break;
	case KeyInput::KeyInputKeycode::KEYCODE_C:
		break;
	case KeyInput::KeyInputKeycode::KEYCODE_D:
		break;
	case KeyInput::KeyInputKeycode::KEYCODE_E:
		std::clog << "You opened your inventory!" << std::endl;

		break;
	case KeyInput::KeyInputKeycode::KEYCODE_F:
		break;
	case KeyInput::KeyInputKeycode::KEYCODE_G:
		break;
	case KeyInput::KeyInputKeycode::KEYCODE_H:
		break;
	case KeyInput::KeyInputKeycode::KEYCODE_I:
		break;
	case KeyInput::KeyInputKeycode::KEYCODE_J:
		break;
	case KeyInput::KeyInputKeycode::KEYCODE_K:
		break;
	case KeyInput::KeyInputKeycode::KEYCODE_L:
		break;
	case KeyInput::KeyInputKeycode::KEYCODE_M:
		break;
	case KeyInput::KeyInputKeycode::KEYCODE_N:
		break;
	case KeyInput::KeyInputKeycode::KEYCODE_O:
		break;
	case KeyInput::KeyInputKeycode::KEYCODE_P:
		break;
	case KeyInput::KeyInputKeycode::KEYCODE_Q:
		break;
	case KeyInput::KeyInputKeycode::KEYCODE_R:
		break;
	case KeyInput::KeyInputKeycode::KEYCODE_S:
		break;
	case KeyInput::KeyInputKeycode::KEYCODE_T:
		break;
	case KeyInput::KeyInputKeycode::KEYCODE_U:
		break;
	case KeyInput::KeyInputKeycode::KEYCODE_V:
		break;
	case KeyInput::KeyInputKeycode::KEYCODE_W:
		break;
	case KeyInput::KeyInputKeycode::KEYCODE_X:
		break;
	case KeyInput::KeyInputKeycode::KEYCODE_Y:
		break;
	case KeyInput::KeyInputKeycode::KEYCODE_Z:
		break;
	case KeyInput::KeyInputKeycode::KEYCODE_NUMPAD_0:
		break;
	case KeyInput::KeyInputKeycode::KEYCODE_NUMPAD_1:
		break;
	case KeyInput::KeyInputKeycode::KEYCODE_NUMPAD_2:
		break;
	case KeyInput::KeyInputKeycode::KEYCODE_NUMPAD_3:
		break;
	case KeyInput::KeyInputKeycode::KEYCODE_NUMPAD_4:
		break;
	case KeyInput::KeyInputKeycode::KEYCODE_NUMPAD_5:
		break;
	case KeyInput::KeyInputKeycode::KEYCODE_NUMPAD_6:
		break;
	case KeyInput::KeyInputKeycode::KEYCODE_NUMPAD_7:
		break;
	case KeyInput::KeyInputKeycode::KEYCODE_NUMPAD_8:
		break;
	case KeyInput::KeyInputKeycode::KEYCODE_NUMPAD_9:
		break;
	case KeyInput::KeyInputKeycode::KEYCODE_MULTIPLY:
		break;
	case KeyInput::KeyInputKeycode::KEYCODE_ADD:
		break;
	case KeyInput::KeyInputKeycode::KEYCODE_SEPARATOR:
		break;
	case KeyInput::KeyInputKeycode::KEYCODE_SUBTRACT:
		break;
	case KeyInput::KeyInputKeycode::KEYCODE_DECIMAL:
		break;
	case KeyInput::KeyInputKeycode::KEYCODE_DIVIDE:
		break;
	case KeyInput::KeyInputKeycode::KEYCODE_F1:
		break;
	case KeyInput::KeyInputKeycode::KEYCODE_F2:
		break;
	case KeyInput::KeyInputKeycode::KEYCODE_F3:
		break;
	case KeyInput::KeyInputKeycode::KEYCODE_F4:
		break;
	case KeyInput::KeyInputKeycode::KEYCODE_F5:
		break;
	case KeyInput::KeyInputKeycode::KEYCODE_F6:
		break;
	case KeyInput::KeyInputKeycode::KEYCODE_F7:
		break;
	case KeyInput::KeyInputKeycode::KEYCODE_F8:
		break;
	case KeyInput::KeyInputKeycode::KEYCODE_F9:
		break;
	case KeyInput::KeyInputKeycode::KEYCODE_F10:
		break;
	case KeyInput::KeyInputKeycode::KEYCODE_F11:
		break;
	case KeyInput::KeyInputKeycode::KEYCODE_F12:
		break;
	case KeyInput::KeyInputKeycode::KEYCODE_F13:
		break;
	case KeyInput::KeyInputKeycode::KEYCODE_F14:
		break;
	case KeyInput::KeyInputKeycode::KEYCODE_F15:
		break;
	case KeyInput::KeyInputKeycode::KEYCODE_F16:
		break;
	case KeyInput::KeyInputKeycode::KEYCODE_F17:
		break;
	case KeyInput::KeyInputKeycode::KEYCODE_F18:
		break;
	case KeyInput::KeyInputKeycode::KEYCODE_F19:
		break;
	case KeyInput::KeyInputKeycode::KEYCODE_F20:
		break;
	case KeyInput::KeyInputKeycode::KEYCODE_F21:
		break;
	case KeyInput::KeyInputKeycode::KEYCODE_F22:
		break;
	case KeyInput::KeyInputKeycode::KEYCODE_F23:
		break;
	case KeyInput::KeyInputKeycode::KEYCODE_F24:
		break;
	case KeyInput::KeyInputKeycode::KEYCODE_NUMPAD_LOCK:
		break;
	case KeyInput::KeyInputKeycode::KEYCODE_LEFT_SHIFT:
		break;
	case KeyInput::KeyInputKeycode::KEYCODE_RIGHT_SHIFT:
		break;
	case KeyInput::KeyInputKeycode::KEYCODE_LEFT_CONTROL:
		break;
	case KeyInput::KeyInputKeycode::KEYCODE_RIGHT_CONTROL:
		break;
	case KeyInput::KeyInputKeycode::KEYCODE_NULL: default:
		// undefined character is processed
		std::cerr << "Processed undefined character!" << std::endl;

		break;
	}
}

// Provided by MessageSystemNode
// Gets automatically called by calling MessageSystem::Notify()
void InputSystem::onNotify(Message message)
{
	
}