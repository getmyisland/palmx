#ifndef MODULE_MANAGER_H
#define MODULE_MANAGER_H
#ifdef _WIN32
#pragma once
#endif

#include "C_ModuleEvent.h"
#include <Windows.h>

class ModuleManager
{
public:
	static ModuleManager& Instance();

	void StartEngine(HINSTANCE p_hInst);
	void SendEventToSystems(C_ModuleEvent p_CSystemEvent);

	HINSTANCE* GetHInstance()
	{
		return &m_hInstance;
	}

private:
	ModuleManager() {};

	// The instance of the engine
	HINSTANCE m_hInstance = nullptr;

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