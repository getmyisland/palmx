#pragma once

#include "AppSystem/AppSystem.h"
#include "InputSystem/InputSystem.h"

class SystemManager {
public:
	static SystemManager& GetInstance() {
		static SystemManager    instance; // Guaranteed to be destroyed.
							  // Instantiated on first use.
		return instance;
	};

	// Inits all subsystems
	void InitSystems();

	// Updates all subsystems
	void UpdateSystems();

	// Shutdown all subsystems
	void ShutDownSystems();

private:
	SystemManager() {};

	bool isGameRunning = true;

	// List of all subsystems
	AppSystem gAppSystem;
	InputSystem gInputSystem;

public:
	SystemManager(SystemManager const&) = delete;
	void operator=(SystemManager const&) = delete;

	// Getter for all subsystems
	AppSystem GetAppSystem() { return gAppSystem; }
	InputSystem GetInputSystem() { return gInputSystem; }
};