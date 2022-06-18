#pragma once

#include "MessageSystem/MessageSystem.h"
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

	// Sends a Message Event to all registered subsystems
	void SendMessageEvent(Message message);

private:
	SystemManager() {};

	// List of all subsystems
	MessageSystem gMessageSystem;
	MessageSystem* gMessageSystemPointer = &gMessageSystem;

	InputSystem gInputSystem = InputSystem(gMessageSystemPointer);

public:
	SystemManager(SystemManager const&) = delete;
	void operator=(SystemManager const&) = delete;
};