#include "InputMapper.h"
#include <iostream>

InputMapper::InputMapper() {};
InputMapper::~InputMapper() {};

void InputMapper::MapKeyboardInputToAction(DWORD wVirtKey)
{
	std::clog << wVirtKey << std::endl;
}