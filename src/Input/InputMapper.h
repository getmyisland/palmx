#ifndef INPUT_MAPPER_H
#define INPUT_MAPPER_H
#ifdef _WIN32
#pragma once
#endif

#include <Windows.h>

// See https://www.gamedev.net/blogs/entry/2250186-designing-a-robust-input-handling-system-for-games/
class InputMapper {
public:
	InputMapper();
	~InputMapper();

	void MapKeyboardInputToAction(DWORD p_dwVirtKey);
};

#endif // INPUT_MAPPER_H