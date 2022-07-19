#ifndef C_INPUT_MAPPER_H
#define C_INPUT_MAPPER_H
#ifdef _WIN32
#pragma once
#endif

#include <Windows.h>

// See https://www.gamedev.net/blogs/entry/2250186-designing-a-robust-input-handling-system-for-games/
class C_InputMapper
{
public:
	C_InputMapper();
	~C_InputMapper();

	void MapKeyboardInputToAction(DWORD p_dwVirtKey);
};

#endif // C_INPUT_MAPPER_H