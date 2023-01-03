#include "InputMapper.h"
#include <iostream>

InputMapper::InputMapper() {};
InputMapper::~InputMapper() {};

void InputMapper::MapKeyboardInputToAction(DWORD p_dwVirtKey)
{
	std::wclog << p_dwVirtKey << std::endl;


}