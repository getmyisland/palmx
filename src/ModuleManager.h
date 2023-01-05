#ifndef MODULE_MANAGER_H
#define MODULE_MANAGER_H
#ifdef _WIN32
#pragma once
#endif

#define MODULE_MANAGER ModuleManager::GetInstance()

#include "ModuleEvent.h"
#include <Windows.h>

class ModuleManager
{
public:
	static ModuleManager& GetInstance()
	{
		static ModuleManager instance;

		return instance;
	}

	ModuleManager(ModuleManager const&) = delete;
	void operator=(ModuleManager const&) = delete;

private:
	ModuleManager() {};

	// The instance of the engine
	HINSTANCE* m_hInstance = nullptr;

	bool game_running = true;

	void InitModules();
	void GameLoop();
	void UpdateModules();
	void RenderModules();
	void ShutdownModules();

public:
	HINSTANCE* GetEngineInstance();

	void StartEngine(HINSTANCE* p_hInst);
	void SendEventToSystems(ModuleEvent p_CSystemEvent);
	void KillGameLoop();
};

#endif // MODULE_MANAGER_H