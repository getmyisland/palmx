#pragma once

#include "MessageSystem/MessageSystem.h"
#include "InputSystem/InputSystem.h"
#include "RenderingSystem/RenderSystem.h"

class ISystem {
public:
	static ISystem& getInstance() {
		static ISystem    instance; // Guaranteed to be destroyed.
							  // Instantiated on first use.
		return instance;
	};

	// Inits all subsystems
	void InitSystems();

	// Updates all subsystems
	void UpdateSystems();

	// Shutdown all subsystems
	void ShutDownSystems();

	void SendMessageEventToQueue(Message message);
	void NotifyMessageNodes();

private:
	ISystem() {};

	// List of all subsystems
	MessageSystem g_MessageSystem;
	InputSystem g_InputSystem = InputSystem(&g_MessageSystem);
	RenderSystem g_RenderSystem = RenderSystem(&g_MessageSystem);

public:
	ISystem(ISystem const&) = delete;
	void operator=(ISystem const&) = delete;
};