#pragma once

#include <Windows.h>

// See https://www.gamedev.net/blogs/entry/2250186-designing-a-robust-input-handling-system-for-games/
class InputMapper {
public:
	InputMapper();
	~InputMapper();

	void MapKeyboardInputToAction(DWORD wVirtKey);
};