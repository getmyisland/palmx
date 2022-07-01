#include "InputSystem.h"

InputSystem::InputSystem() {};
InputSystem::~InputSystem() {};

void InputSystem::Init()
{
	g_InputCollector.EnableLowLevelHooks();
}

void InputSystem::Update()
{
}

void InputSystem::Shutdown()
{
}

void InputSystem::OnEvent(SystemEvent sysEvent)
{
}
