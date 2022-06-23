#include <iostream>
#include "InputMapper.h"

// Map the keyboard input to a function
void InputMapper::MapKeyboardInput(KeyboardInput::KeyInputType keyboardInputType, KeyboardInput::KeyInputKeycode keyboardInputKeycode)
{
	switch (keyboardInputKeycode) {
	case KeyboardInput::KeyInputKeycode::KEYCODE_LEFT_MOUSE:
		break;
	case KeyboardInput::KeyInputKeycode::KEYCODE_RIGHT_MOUSE:
		break;
	case KeyboardInput::KeyInputKeycode::KEYCODE_CONTROL_BREAK_PROCESSING:
		break;
	case KeyboardInput::KeyInputKeycode::KEYCODE_MIDDLE_MOUSE:
		break;
	case KeyboardInput::KeyInputKeycode::KEYCODE_BACKSPACE:
		break;
	case KeyboardInput::KeyInputKeycode::KEYCODE_TAB:
		std::clog << "You opened the scoreboard!" << std::endl;

		break;
	case KeyboardInput::KeyInputKeycode::KEYCODE_RETURN:
		break;
	case KeyboardInput::KeyInputKeycode::KEYCODE_SHIFT:
		std::clog << "You are running!" << std::endl;

		break;
	case KeyboardInput::KeyInputKeycode::KEYCODE_CONTROL:
		break;
	case KeyboardInput::KeyInputKeycode::KEYCODE_ALT:
		break;
	case KeyboardInput::KeyInputKeycode::KEYCODE_PAUSE:
		break;
	case KeyboardInput::KeyInputKeycode::KEYCODE_CAPITAL:
		break;
	case KeyboardInput::KeyInputKeycode::KEYCODE_ESCAPE:
		break;
	case KeyboardInput::KeyInputKeycode::KEYCODE_SPACE:
		break;
	case KeyboardInput::KeyInputKeycode::KEYCODE_ARROW_LEFT:
		break;
	case KeyboardInput::KeyInputKeycode::KEYCODE_ARROW_UP:
		break;
	case KeyboardInput::KeyInputKeycode::KEYCODE_ARROW_RIGHT:
		break;
	case KeyboardInput::KeyInputKeycode::KEYCODE_ARROW_DOWN:
		break;
	case KeyboardInput::KeyInputKeycode::KEYCODE_0:
		break;
	case KeyboardInput::KeyInputKeycode::KEYCODE_1:
		break;
	case KeyboardInput::KeyInputKeycode::KEYCODE_2:
		break;
	case KeyboardInput::KeyInputKeycode::KEYCODE_3:
		break;
	case KeyboardInput::KeyInputKeycode::KEYCODE_4:
		break;
	case KeyboardInput::KeyInputKeycode::KEYCODE_5:
		break;
	case KeyboardInput::KeyInputKeycode::KEYCODE_6:
		break;
	case KeyboardInput::KeyInputKeycode::KEYCODE_7:
		break;
	case KeyboardInput::KeyInputKeycode::KEYCODE_8:
		break;
	case KeyboardInput::KeyInputKeycode::KEYCODE_9:
		break;
	case KeyboardInput::KeyInputKeycode::KEYCODE_A:
		break;
	case KeyboardInput::KeyInputKeycode::KEYCODE_B:
		break;
	case KeyboardInput::KeyInputKeycode::KEYCODE_C:
		break;
	case KeyboardInput::KeyInputKeycode::KEYCODE_D:
		break;
	case KeyboardInput::KeyInputKeycode::KEYCODE_E:
		std::clog << "You opened your inventory!" << std::endl;

		break;
	case KeyboardInput::KeyInputKeycode::KEYCODE_F:
		break;
	case KeyboardInput::KeyInputKeycode::KEYCODE_G:
		break;
	case KeyboardInput::KeyInputKeycode::KEYCODE_H:
		break;
	case KeyboardInput::KeyInputKeycode::KEYCODE_I:
		break;
	case KeyboardInput::KeyInputKeycode::KEYCODE_J:
		break;
	case KeyboardInput::KeyInputKeycode::KEYCODE_K:
		break;
	case KeyboardInput::KeyInputKeycode::KEYCODE_L:
		break;
	case KeyboardInput::KeyInputKeycode::KEYCODE_M:
		break;
	case KeyboardInput::KeyInputKeycode::KEYCODE_N:
		break;
	case KeyboardInput::KeyInputKeycode::KEYCODE_O:
		break;
	case KeyboardInput::KeyInputKeycode::KEYCODE_P:
		break;
	case KeyboardInput::KeyInputKeycode::KEYCODE_Q:
		break;
	case KeyboardInput::KeyInputKeycode::KEYCODE_R:
		break;
	case KeyboardInput::KeyInputKeycode::KEYCODE_S:
		break;
	case KeyboardInput::KeyInputKeycode::KEYCODE_T:
		break;
	case KeyboardInput::KeyInputKeycode::KEYCODE_U:
		break;
	case KeyboardInput::KeyInputKeycode::KEYCODE_V:
		break;
	case KeyboardInput::KeyInputKeycode::KEYCODE_W:
		break;
	case KeyboardInput::KeyInputKeycode::KEYCODE_X:
		break;
	case KeyboardInput::KeyInputKeycode::KEYCODE_Y:
		break;
	case KeyboardInput::KeyInputKeycode::KEYCODE_Z:
		break;
	case KeyboardInput::KeyInputKeycode::KEYCODE_NUMPAD_0:
		break;
	case KeyboardInput::KeyInputKeycode::KEYCODE_NUMPAD_1:
		break;
	case KeyboardInput::KeyInputKeycode::KEYCODE_NUMPAD_2:
		break;
	case KeyboardInput::KeyInputKeycode::KEYCODE_NUMPAD_3:
		break;
	case KeyboardInput::KeyInputKeycode::KEYCODE_NUMPAD_4:
		break;
	case KeyboardInput::KeyInputKeycode::KEYCODE_NUMPAD_5:
		break;
	case KeyboardInput::KeyInputKeycode::KEYCODE_NUMPAD_6:
		break;
	case KeyboardInput::KeyInputKeycode::KEYCODE_NUMPAD_7:
		break;
	case KeyboardInput::KeyInputKeycode::KEYCODE_NUMPAD_8:
		break;
	case KeyboardInput::KeyInputKeycode::KEYCODE_NUMPAD_9:
		break;
	case KeyboardInput::KeyInputKeycode::KEYCODE_MULTIPLY:
		break;
	case KeyboardInput::KeyInputKeycode::KEYCODE_ADD:
		break;
	case KeyboardInput::KeyInputKeycode::KEYCODE_SEPARATOR:
		break;
	case KeyboardInput::KeyInputKeycode::KEYCODE_SUBTRACT:
		break;
	case KeyboardInput::KeyInputKeycode::KEYCODE_DECIMAL:
		break;
	case KeyboardInput::KeyInputKeycode::KEYCODE_DIVIDE:
		break;
	case KeyboardInput::KeyInputKeycode::KEYCODE_F1:
		break;
	case KeyboardInput::KeyInputKeycode::KEYCODE_F2:
		break;
	case KeyboardInput::KeyInputKeycode::KEYCODE_F3:
		break;
	case KeyboardInput::KeyInputKeycode::KEYCODE_F4:
		break;
	case KeyboardInput::KeyInputKeycode::KEYCODE_F5:
		break;
	case KeyboardInput::KeyInputKeycode::KEYCODE_F6:
		break;
	case KeyboardInput::KeyInputKeycode::KEYCODE_F7:
		break;
	case KeyboardInput::KeyInputKeycode::KEYCODE_F8:
		break;
	case KeyboardInput::KeyInputKeycode::KEYCODE_F9:
		break;
	case KeyboardInput::KeyInputKeycode::KEYCODE_F10:
		break;
	case KeyboardInput::KeyInputKeycode::KEYCODE_F11:
		break;
	case KeyboardInput::KeyInputKeycode::KEYCODE_F12:
		break;
	case KeyboardInput::KeyInputKeycode::KEYCODE_F13:
		break;
	case KeyboardInput::KeyInputKeycode::KEYCODE_F14:
		break;
	case KeyboardInput::KeyInputKeycode::KEYCODE_F15:
		break;
	case KeyboardInput::KeyInputKeycode::KEYCODE_F16:
		break;
	case KeyboardInput::KeyInputKeycode::KEYCODE_F17:
		break;
	case KeyboardInput::KeyInputKeycode::KEYCODE_F18:
		break;
	case KeyboardInput::KeyInputKeycode::KEYCODE_F19:
		break;
	case KeyboardInput::KeyInputKeycode::KEYCODE_F20:
		break;
	case KeyboardInput::KeyInputKeycode::KEYCODE_F21:
		break;
	case KeyboardInput::KeyInputKeycode::KEYCODE_F22:
		break;
	case KeyboardInput::KeyInputKeycode::KEYCODE_F23:
		break;
	case KeyboardInput::KeyInputKeycode::KEYCODE_F24:
		break;
	case KeyboardInput::KeyInputKeycode::KEYCODE_NUMPAD_LOCK:
		break;
	case KeyboardInput::KeyInputKeycode::KEYCODE_LEFT_SHIFT:
		break;
	case KeyboardInput::KeyInputKeycode::KEYCODE_RIGHT_SHIFT:
		break;
	case KeyboardInput::KeyInputKeycode::KEYCODE_LEFT_CONTROL:
		break;
	case KeyboardInput::KeyInputKeycode::KEYCODE_RIGHT_CONTROL:
		break;
	case KeyboardInput::KeyInputKeycode::KEYCODE_NULL: default:
		// undefined character is processed
		std::cerr << "Processed undefined character!" << std::endl;

		break;
	}
}
