#ifndef SYSTEMHANDLER_H
#define SYSTEMHANDLER_H
#ifdef _WIN32
#pragma once
#endif

#include "CSystemEvent.h"
#include "input/InputSystem.h"
#include "gui/GuiSystem.h"

class SystemHandler
{
public:
	static SystemHandler& Instance();

	void StartEngine(HINSTANCE p_hInst);
	void SendEventToSystems(CSystemEvent p_CSystemEvent);

	HINSTANCE* GetHInstance() { return &m_hInstance; }

	InputSystem* GetInputSystem() { return &m_InputSystem; }
	GuiSystem* GetGUI() { return &m_GUI; }

private:
	SystemHandler() {};

	// Systems
	InputSystem m_InputSystem;
	GuiSystem m_GUI;

	// The instance of the engine
	HINSTANCE m_hInstance = nullptr;

	void InitSystems();
	void UpdateSystems();
	void ShutdownSystems();

public:
	SystemHandler(SystemHandler const&) = delete;
	void operator=(SystemHandler const&) = delete;
};

#endif // SYSTEMHANDLER_H