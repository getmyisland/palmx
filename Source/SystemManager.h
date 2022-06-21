#pragma once

#include "MessageSystem/MessageSystem.h"
#include "InputSystem/InputSystem.h"
#include "RenderingSystem/RenderSystem.h"

class SystemManager {
public:
	static SystemManager& getInstance() {
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
	void SendMessageEventToQueue(Message message);

	// Calls the Notify() function in the MessageSystem
	void NotifyMessageSystem();

	// Getters for systems
	MessageSystem getMessageSystem() { return g_MessageSystem; }
	InputSystem getInputSystem() { return g_InputSystem; }
	RenderSystem getRenderSystem() { return g_RenderSystem; }

	// Getters for variables

private:
	SystemManager() {};

	// List of all subsystems
	MessageSystem g_MessageSystem;
	MessageSystem* g_MessageSystemPointer = &g_MessageSystem;

	InputSystem g_InputSystem = InputSystem(g_MessageSystemPointer);
	RenderSystem g_RenderSystem = RenderSystem(g_MessageSystemPointer);

	// Variables

public:
	SystemManager(SystemManager const&) = delete;
	void operator=(SystemManager const&) = delete;
};