#ifndef INPUT_COLLECTOR_H
#define INPUT_COLLECTOR_H
#ifdef _WIN32
#pragma once
#endif

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

#endif // INPUT_COLLECTOR_H