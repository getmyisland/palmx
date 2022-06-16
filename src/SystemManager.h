#pragma once

#include "AppSystem/AppSystem.cpp"
#include "InputSystem/InputSystem.cpp"

class SystemManager {
public:
	static SystemManager& GetInstance()
	{
		static SystemManager    instance; // Guaranteed to be destroyed.
							  // Instantiated on first use.
		return instance;
	}

	// List of all subsystems
	AppSystem& gAppSystem = AppSystem::GetInstance();
	InputSystem& gInputSystem = InputSystem::GetInstance();

	void InitSystems() {
		// Init all subsystems
		gAppSystem.Init();
		
	}

	void UpdateSystems() {
		while (true) {
			// Update all subsystems
			gInputSystem.UpdateInput();
		}
	}

	void ShutDownSystems() {
		//Shutdown all subsystems

	}

private:
	SystemManager() {};

public:
	SystemManager(SystemManager const&) = delete;
	void operator=(SystemManager const&) = delete;
};