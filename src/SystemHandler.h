#pragma once

#include "SystemEvent.h"
#include "Input/InputSystem.h"
#include "GUI/GUI.h"

class SystemHandler
{
public:
	static SystemHandler& Instance();

	void InitSystems(HINSTANCE *hInst);
	void UpdateSystems();
	void ShutdownSystems();
	void SendEventToSystems(SystemEvent sysEvent);

	HINSTANCE* GetInstance() { return p_hInstance; }

	InputSystem* GetInputSystem() { return &g_InputSystem; }
	GUI* GetGUI() { return &g_GUI; }

private:
	SystemHandler() {};

	// Systems
	InputSystem g_InputSystem;
	GUI g_GUI;

	// The instance of the engine
	HINSTANCE *p_hInstance = nullptr;

public:
	SystemHandler(SystemHandler const&) = delete;
	void operator=(SystemHandler const&) = delete;
};