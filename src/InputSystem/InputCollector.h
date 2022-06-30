#pragma once

#include <Windows.h>
#include "InputMapper.h"

class InputCollector {
public:
	InputCollector(InputMapper* inputMapper);
	~InputCollector();

	void EnableLowLevelHooks();
	void SendKeyboardInputToInputMapper(DWORD wVirtKey);

	InputMapper* p_InputMapper = nullptr;
};