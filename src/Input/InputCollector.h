#pragma once

#include <Windows.h>
#include "InputMapper.h"

class InputCollector {
public:
	InputCollector(InputMapper* p_pInputMapper);
	~InputCollector();

	void EnableLowLevelHooks();
	void SendKeyboardInputToInputMapper(DWORD p_dwVirtKey);

	InputMapper* m_pInputMapper = nullptr;
};