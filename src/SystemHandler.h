#pragma once

#include "SystemHandler.fwd.h"
#include "SystemEvent.h"
#include "Input/InputSystem.fwd.h"
#include "GUI/GUI.fwd.h"

class SystemHandler
{
public:
	static SystemHandler& Instance();

	void StartEngine(HINSTANCE hInst);
	void SendEventToSystems(SystemEvent sysEvent);

	HINSTANCE* GetInstance() { return &hInstance; }

	InputSystem* GetInputSystem() { return &g_InputSystem; }
	GUI* GetGUI() { return &g_GUI; }

private:
	SystemHandler() {};

	// Systems
	InputSystem g_InputSystem;
	GUI g_GUI;

	// The instance of the engine
	HINSTANCE hInstance = nullptr;

	void InitSystems();
	void UpdateSystems();
	void ShutdownSystems();

public:
	SystemHandler(SystemHandler const&) = delete;
	void operator=(SystemHandler const&) = delete;
};