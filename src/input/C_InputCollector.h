#ifndef C_INPUT_COLLECTOR_H
#define C_INPUT_COLLECTOR_H
#ifdef _WIN32
#pragma once
#endif

#include <Windows.h>
#include "C_InputMapper.h"

class C_InputCollector
{
public:
	C_InputCollector(C_InputMapper* p_pInputMapper);
	~C_InputCollector();

	void EnableLowLevelHooks();
	void SendKeyboardInputToInputMapper(DWORD p_dwVirtKey);

	C_InputMapper* m_pInputMapper = nullptr;
};

#endif // C_INPUT_COLLECTOR_H