#ifndef MODULE_MANAGER_H
#define MODULE_MANAGER_H
#ifdef _WIN32
#pragma once
#endif

#include "ModuleEvent.h"
#include <Windows.h>

class ModuleManager
{
public:
	static ModuleManager& Instance();

	void StartEngine(HINSTANCE p_hInst);
	void SendEventToSystems(ModuleEvent p_CSystemEvent);
	void KillGameLoop();

	HINSTANCE* GetHInstance();

private:
	ModuleManager() {};

	// The instance of the engine
	HINSTANCE m_hInstance = nullptr;

	bool game_running = true;

	void InitSystems();
	void GameLoop();
	void UpdateSystems();
	void RenderSystems();
	void ShutdownSystems();

public:
	ModuleManager(ModuleManager const&) = delete;
	void operator=(ModuleManager const&) = delete;
};

#endif // MODULE_MANAGER_H