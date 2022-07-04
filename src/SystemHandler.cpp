#include "SystemHandler.h"
#include <iostream>
#include <Windows.h>

SystemHandler& SystemHandler::Instance() {
	static SystemHandler    instance;

	return instance;
};

void SystemHandler::StartEngine(HINSTANCE hInst) {
	hInstance = hInst;

	InitSystems();

	UpdateSystems();

	ShutdownSystems();
}

void SystemHandler::InitSystems() {
	g_InputSystem.Init();
	g_GUI.Init();
}

void SystemHandler::UpdateSystems() {
	// Main game loop
	MSG msg;

	while (GetMessage(&msg, nullptr, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);

		g_InputSystem.Update();
		g_GUI.Update();
	}
}

void SystemHandler::ShutdownSystems() {
	g_InputSystem.Shutdown();
	g_GUI.Shutdown();
}

void SystemHandler::SendEventToSystems(SystemEvent sysEvent) {
	g_InputSystem.OnEvent(sysEvent);
	g_GUI.OnEvent(sysEvent);
}