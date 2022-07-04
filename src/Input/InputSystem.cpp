#include "InputSystem.h"

InputSystem::InputSystem() {};
InputSystem::~InputSystem() {};

void InputSystem::Init()
{
	m_InputCollector.EnableLowLevelHooks();
}

void InputSystem::Update()
{
}

void InputSystem::Shutdown()
{
}

void InputSystem::OnEvent(SystemEvent i_SysEvent)
{
}
