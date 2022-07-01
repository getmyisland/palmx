#include "SystemHandler.h"
#include <iostream>
#include <Windows.h>

SystemHandler& SystemHandler::Instance() {
	static SystemHandler    instance;

	return instance;
};

void SystemHandler::InitSystems(HINSTANCE *hInst) {
	p_hInstance = hInst;
	
	g_InputSystem.Init();
	g_GUI.Init();
}

void SystemHandler::UpdateSystems() {
	g_InputSystem.Update();
	g_GUI.Update();
}

void SystemHandler::ShutdownSystems() {
	g_InputSystem.Shutdown();
	g_GUI.Shutdown();
}

void SystemHandler::SendEventToSystems(SystemEvent sysEvent) {
	g_InputSystem.OnEvent(sysEvent);
	g_InputSystem.OnEvent(sysEvent);
}