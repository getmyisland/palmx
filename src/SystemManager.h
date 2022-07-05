#ifndef SYSTEM_MANAGER_H
#define SYSTEM_MANAGER_H
#ifdef _WIN32
#pragma once
#endif

#include "CSystemEvent.h"
#include <Windows.h>

class SystemManager
{
public:
	static SystemManager& Instance();

	void StartEngine(HINSTANCE p_hInst);
	void SendEventToSystems(CSystemEvent p_CSystemEvent);

	HINSTANCE* GetHInstance() { return &m_hInstance; }

private:
	SystemManager() {};

	// The instance of the engine
	HINSTANCE m_hInstance = nullptr;

	void InitSystems();
	void GameLoop();
	void UpdateSystems();
	void RenderSystems();
	void ShutdownSystems();

public:
	SystemManager(SystemManager const&) = delete;
	void operator=(SystemManager const&) = delete;
};

#endif // SYSTEM_MANAGER_H