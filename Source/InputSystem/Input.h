#pragma once

class KeyInput {
public:
	const enum class KeyInputType {
		INPUT_KEYBOARD_KEY_DOWN,
		INPUT_KEYBOARD_KEY_UP
	};

	// Virtual Key Codes see https://docs.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes
	const enum class KeyInputKeycode {
		KEYCODE_NULL, // NULL
		KEYCODE_LEFT_MOUSE, //0x01
		KEYCODE_RIGHT_MOUSE, //0x02
		KEYCODE_CONTROL_BREAK_PROCESSING, //0x03
		KEYCODE_MIDDLE_MOUSE, //0x04
		KEYCODE_BACKSPACE, //0x08
		KEYCODE_TAB, //0x09
		KEYCODE_RETURN, //0x0D
		KEYCODE_SHIFT, //0x10
		KEYCODE_CONTROL, //0x11
		KEYCODE_ALT, //0x12
		KEYCODE_PAUSE, //0x13
		KEYCODE_CAPITAL, //0x14
		KEYCODE_ESCAPE, //0x1B
		KEYCODE_SPACE, //0x20
		KEYCODE_ARROW_LEFT, //0x25
		KEYCODE_ARROW_UP, //0x26
		KEYCODE_ARROW_RIGHT, //0x27
		KEYCODE_ARROW_DOWN, //0x28
		KEYCODE_0, //0x30
		KEYCODE_1, //0x31
		KEYCODE_2, //0x32
		KEYCODE_3, //0x33
		KEYCODE_4, //0x34
		KEYCODE_5, //0x35
		KEYCODE_6, //0x36
		KEYCODE_7, //0x37
		KEYCODE_8, //0x38
		KEYCODE_9, //0x39
		KEYCODE_A, //0x41
		KEYCODE_B, //0x42
		KEYCODE_C, //0x43
		KEYCODE_D, //0x44
		KEYCODE_E, //0x45
		KEYCODE_F, //0x46
		KEYCODE_G, //0x47
		KEYCODE_H, //0x48
		KEYCODE_I, //0x49
		KEYCODE_J, //0x4A
		KEYCODE_K, //0x4B
		KEYCODE_L, //0x4C
		KEYCODE_M, //0x4D
		KEYCODE_N, //0x4E
		KEYCODE_O, //0x4F
		KEYCODE_P, //0x50
		KEYCODE_Q, //0x51
		KEYCODE_R, //0x52
		KEYCODE_S, //0x53
		KEYCODE_T, //0x54
		KEYCODE_U, //0x55
		KEYCODE_V, //0x56
		KEYCODE_W, //0x57
		KEYCODE_X, //0x58
		KEYCODE_Y, //0x59
		KEYCODE_Z, //0x5A
		KEYCODE_NUMPAD_0, //0x60
		KEYCODE_NUMPAD_1, //0x61
		KEYCODE_NUMPAD_2, //0x62
		KEYCODE_NUMPAD_3, //0x63
		KEYCODE_NUMPAD_4, //0x64
		KEYCODE_NUMPAD_5, //0x65
		KEYCODE_NUMPAD_6, //0x66
		KEYCODE_NUMPAD_7, //0x67
		KEYCODE_NUMPAD_8, //0x68
		KEYCODE_NUMPAD_9, //0x69
		KEYCODE_MULTIPLY, //0x6A
		KEYCODE_ADD, //0x6B
		KEYCODE_SEPARATOR, //0x6C
		KEYCODE_SUBTRACT, //0x6D
		KEYCODE_DECIMAL, //0x6E
		KEYCODE_DIVIDE, //0x6F
		KEYCODE_F1, //0x70
		KEYCODE_F2, //0x71
		KEYCODE_F3, //0x72
		KEYCODE_F4, //0x73
		KEYCODE_F5, //0x74
		KEYCODE_F6, //0x75
		KEYCODE_F7, //0x76
		KEYCODE_F8, //0x77
		KEYCODE_F9, //0x78
		KEYCODE_F10, //0x79
		KEYCODE_F11, //0x7A
		KEYCODE_F12, //0x7B
		KEYCODE_F13, //0x7C
		KEYCODE_F14, //0x7D
		KEYCODE_F15, //0x7E
		KEYCODE_F16, //0x7F
		KEYCODE_F17, //0x80
		KEYCODE_F18, //0x81
		KEYCODE_F19, //0x82
		KEYCODE_F20, //0x83
		KEYCODE_F21, //0x84
		KEYCODE_F22, //0x85
		KEYCODE_F23, //0x86
		KEYCODE_F24, //0x87
		KEYCODE_NUMPAD_LOCK, //0x90
		KEYCODE_LEFT_SHIFT, //0xA0
		KEYCODE_RIGHT_SHIFT, //0xA1
		KEYCODE_LEFT_CONTROL, //0xA2
		KEYCODE_RIGHT_CONTROL, //0xA3
	};

	KeyInput(KeyInputType type, char input) {
		inputType = type;
		inputChar = input;
	}
	~KeyInput() {};

	KeyInputType getKeyInputType() { return inputType; }
	char getInputChar() { return inputChar; }

	std::map<std::string, KeyInputKeycode> keycodeInputMap = {
		{"NULL", KeyInputKeycode::KEYCODE_NULL}, // Default null value
		{"0x01", KeyInputKeycode::KEYCODE_LEFT_MOUSE}, //0x01
		{"0x02", KeyInputKeycode::KEYCODE_RIGHT_MOUSE}, //0x02
		{"0x03", KeyInputKeycode::KEYCODE_CONTROL_BREAK_PROCESSING}, //0x03
		{"0x04", KeyInputKeycode::KEYCODE_MIDDLE_MOUSE}, //0x04
		{"0x08", KeyInputKeycode::KEYCODE_BACKSPACE}, //0x08
		{"0x09", KeyInputKeycode::KEYCODE_TAB}, //0x09
		{"0x0D", KeyInputKeycode::KEYCODE_RETURN}, //0x0D
		{"0x10", KeyInputKeycode::KEYCODE_SHIFT}, //0x10
		{"0x11", KeyInputKeycode::KEYCODE_CONTROL}, //0x11
		{"0x12", KeyInputKeycode::KEYCODE_ALT}, //0x12
		{"0x13", KeyInputKeycode::KEYCODE_PAUSE}, //0x13
		{"0x14", KeyInputKeycode::KEYCODE_CAPITAL}, //0x14
		{"0x1B", KeyInputKeycode::KEYCODE_ESCAPE}, //0x1B
		{"0x20", KeyInputKeycode::KEYCODE_SPACE}, //0x20
		{"0x25", KeyInputKeycode::KEYCODE_ARROW_LEFT}, //0x25
		{"0x26", KeyInputKeycode::KEYCODE_ARROW_UP}, //0x26
		{"0x27", KeyInputKeycode::KEYCODE_ARROW_RIGHT}, //0x27
		{"0x28", KeyInputKeycode::KEYCODE_ARROW_DOWN}, //0x28
		{"0x30", KeyInputKeycode::KEYCODE_0}, //0x30
		{"0x31", KeyInputKeycode::KEYCODE_1}, //0x31
		{"0x32", KeyInputKeycode::KEYCODE_2}, //0x32
		{"0x33", KeyInputKeycode::KEYCODE_3}, //0x33
		{"0x34", KeyInputKeycode::KEYCODE_4}, //0x34
		{"0x35", KeyInputKeycode::KEYCODE_5}, //0x35
		{"0x36", KeyInputKeycode::KEYCODE_6}, //0x36
		{"0x37", KeyInputKeycode::KEYCODE_7}, //0x37
		{"0x38", KeyInputKeycode::KEYCODE_8}, //0x38
		{"0x39", KeyInputKeycode::KEYCODE_9}, //0x39
		{"0x41", KeyInputKeycode::KEYCODE_A}, //0x41
		{"0x42", KeyInputKeycode::KEYCODE_B}, //0x42
		{"0x43", KeyInputKeycode::KEYCODE_C}, //0x43
		{"0x44", KeyInputKeycode::KEYCODE_D}, //0x44
		{"0x45", KeyInputKeycode::KEYCODE_E}, //0x45
		{"0x46", KeyInputKeycode::KEYCODE_F}, //0x46
		{"0x47", KeyInputKeycode::KEYCODE_G}, //0x47
		{"0x48", KeyInputKeycode::KEYCODE_H}, //0x48
		{"0x49", KeyInputKeycode::KEYCODE_I}, //0x49
		{"0x4A", KeyInputKeycode::KEYCODE_J}, //0x4A
		{"0x4B", KeyInputKeycode::KEYCODE_K}, //0x4B
		{"0x4C", KeyInputKeycode::KEYCODE_L}, //0x4C
		{"0x4D", KeyInputKeycode::KEYCODE_M}, //0x4D
		{"0x4E", KeyInputKeycode::KEYCODE_N}, //0x4E
		{"0x4F", KeyInputKeycode::KEYCODE_O}, //0x4F
		{"0x50", KeyInputKeycode::KEYCODE_P}, //0x50
		{"0x51", KeyInputKeycode::KEYCODE_Q}, //0x51
		{"0x52", KeyInputKeycode::KEYCODE_R}, //0x52
		{"0x53", KeyInputKeycode::KEYCODE_S}, //0x53
		{"0x54", KeyInputKeycode::KEYCODE_T}, //0x54
		{"0x55", KeyInputKeycode::KEYCODE_U}, //0x55
		{"0x56", KeyInputKeycode::KEYCODE_V}, //0x56
		{"0x57", KeyInputKeycode::KEYCODE_W}, //0x57
		{"0x58", KeyInputKeycode::KEYCODE_X}, //0x58
		{"0x59", KeyInputKeycode::KEYCODE_Y}, //0x59
		{"0x5A", KeyInputKeycode::KEYCODE_Z}, //0x5A
		{"0x60", KeyInputKeycode::KEYCODE_NUMPAD_0}, //0x60
		{"0x61", KeyInputKeycode::KEYCODE_NUMPAD_1}, //0x61
		{"0x62", KeyInputKeycode::KEYCODE_NUMPAD_2}, //0x62
		{"0x63", KeyInputKeycode::KEYCODE_NUMPAD_3}, //0x63
		{"0x64", KeyInputKeycode::KEYCODE_NUMPAD_4}, //0x64
		{"0x65", KeyInputKeycode::KEYCODE_NUMPAD_5}, //0x65
		{"0x66", KeyInputKeycode::KEYCODE_NUMPAD_6}, //0x66
		{"0x67", KeyInputKeycode::KEYCODE_NUMPAD_7}, //0x67
		{"0x68", KeyInputKeycode::KEYCODE_NUMPAD_8}, //0x68
		{"0x69", KeyInputKeycode::KEYCODE_NUMPAD_9}, //0x69
		{"0x6A", KeyInputKeycode::KEYCODE_MULTIPLY}, //0x6A
		{"0x6B", KeyInputKeycode::KEYCODE_ADD}, //0x6B
		{"0x6C", KeyInputKeycode::KEYCODE_SEPARATOR}, //0x6C
		{"0x6D", KeyInputKeycode::KEYCODE_SUBTRACT}, //0x6D
		{"0x6E", KeyInputKeycode::KEYCODE_DECIMAL}, //0x6E
		{"0x6F", KeyInputKeycode::KEYCODE_DIVIDE}, //0x6F
		{"0x70", KeyInputKeycode::KEYCODE_F1}, //0x70
		{"0x71", KeyInputKeycode::KEYCODE_F2}, //0x71
		{"0x72", KeyInputKeycode::KEYCODE_F3}, //0x72
		{"0x73", KeyInputKeycode::KEYCODE_F4}, //0x73
		{"0x74", KeyInputKeycode::KEYCODE_F5}, //0x74
		{"0x75", KeyInputKeycode::KEYCODE_F6}, //0x75
		{"0x76", KeyInputKeycode::KEYCODE_F7}, //0x76
		{"0x77", KeyInputKeycode::KEYCODE_F8}, //0x77
		{"0x78", KeyInputKeycode::KEYCODE_F9}, //0x78
		{"0x79", KeyInputKeycode::KEYCODE_F10}, //0x79
		{"0x7A", KeyInputKeycode::KEYCODE_F11}, //0x7A
		{"0x7B", KeyInputKeycode::KEYCODE_F12}, //0x7B
		{"0x7C", KeyInputKeycode::KEYCODE_F13}, //0x7C
		{"0x7D", KeyInputKeycode::KEYCODE_F14}, //0x7D
		{"0x7E", KeyInputKeycode::KEYCODE_F15}, //0x7E
		{"0x7F", KeyInputKeycode::KEYCODE_F16}, //0x7F
		{"0x80", KeyInputKeycode::KEYCODE_F17}, //0x80
		{"0x81", KeyInputKeycode::KEYCODE_F18}, //0x81
		{"0x82", KeyInputKeycode::KEYCODE_F19}, //0x82
		{"0x83", KeyInputKeycode::KEYCODE_F20}, //0x83
		{"0x84", KeyInputKeycode::KEYCODE_F21}, //0x84
		{"0x85", KeyInputKeycode::KEYCODE_F22}, //0x85
		{"0x86", KeyInputKeycode::KEYCODE_F23}, //0x86
		{"0x87", KeyInputKeycode::KEYCODE_F24}, //0x87
		{"0x90", KeyInputKeycode::KEYCODE_NUMPAD_LOCK}, //0x90
		{"0xA0", KeyInputKeycode::KEYCODE_LEFT_SHIFT}, //0xA0
		{"0xA1", KeyInputKeycode::KEYCODE_RIGHT_SHIFT}, //0xA1
		{"0xA2", KeyInputKeycode::KEYCODE_LEFT_CONTROL}, //0xA2
		{"0xA3", KeyInputKeycode::KEYCODE_RIGHT_CONTROL} //0xA3
	};

private:
	KeyInputType inputType;
	char inputChar;
};

class MouseInput {

};