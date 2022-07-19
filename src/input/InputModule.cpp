#include "InputModule.h"

InputModule::InputModule() {};
InputModule::~InputModule() {};

void InputModule::Init()
{
	m_InputCollector.EnableLowLevelHooks();
}

void InputModule::Update() {};

void InputModule::Shutdown()
{
}

void InputModule::OnEvent(C_ModuleEvent* i_CSystemEvent)
{
}
