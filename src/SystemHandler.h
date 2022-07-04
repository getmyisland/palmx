#pragma once

#include "SystemHandler.fwd.h"
#include "SystemEvent.h"
#include "Input/InputSystem.fwd.h"
#include "GUI/GUI.fwd.h"

class SystemHandler
{
public:
	static SystemHandler& Instance();

	void StartEngine(HINSTANCE p_hInst);
	void SendEventToSystems(SystemEvent p_SysEvent);

	HINSTANCE* GetHInstance() { return &m_hInstance; }

	InputSystem* GetInputSystem() { return &m_InputSystem; }
	GUI* GetGUI() { return &m_GUI; }

private:
	SystemHandler() {};

	// Systems
	InputSystem m_InputSystem;
	GUI m_GUI;

	// The instance of the engine
	HINSTANCE m_hInstance = nullptr;

	void InitSystems();
	void UpdateSystems();
	void ShutdownSystems();

public:
	SystemHandler(SystemHandler const&) = delete;
	void operator=(SystemHandler const&) = delete;
};