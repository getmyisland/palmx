#include "SystemHandler.h"
#include <iostream>
#include <Windows.h>

SystemHandler& SystemHandler::Instance() {
	static SystemHandler    instance;

	return instance;
};

void SystemHandler::StartEngine(HINSTANCE hInst) {
	m_hInstance = hInst;

	InitSystems();

	UpdateSystems();

	ShutdownSystems();
}

void SystemHandler::InitSystems() {
	m_InputSystem.Init();
	m_GUI.Init();
}

void SystemHandler::UpdateSystems() {
	// Main game loop
	MSG msg;

	while (GetMessage(&msg, nullptr, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);

		m_InputSystem.Update();
		m_GUI.Update();
	}
}

void SystemHandler::ShutdownSystems() {
	m_InputSystem.Shutdown();
	m_GUI.Shutdown();
}

void SystemHandler::SendEventToSystems(CSystemEvent p_CSystemEvent) {
	m_InputSystem.OnEvent(p_CSystemEvent);
	m_GUI.OnEvent(p_CSystemEvent);
}