#pragma once

#include "SystemEvent.h"
#include "InputSystem/InputSystem.h"
#include "GUI/GuiSystem.h"

class SystemHandler
{
public:
	static SystemHandler& Instance();

	void InitSystems(HINSTANCE *hInst);
	void UpdateSystems();
	void ShutdownSystems();
	void SendEventToSystems(SystemEvent sysEvent);

	HINSTANCE* getInstance() { return p_hInstance; }

private:
	SystemHandler() {};

	// Systems
	InputSystem g_InputSystem;
	GuiSystem g_GuiSystem;

	// The instance of the engine
	HINSTANCE *p_hInstance = nullptr;

public:
	SystemHandler(SystemHandler const&) = delete;
	void operator=(SystemHandler const&) = delete;
};