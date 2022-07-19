#include "C_InputMapper.h"
#include <iostream>

C_InputMapper::C_InputMapper() {};
C_InputMapper::~C_InputMapper() {};

void C_InputMapper::MapKeyboardInputToAction(DWORD p_dwVirtKey)
{
	std::clog << p_dwVirtKey << std::endl;
}