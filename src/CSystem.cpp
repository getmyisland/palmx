#include "CSystem.h"

#include <iostream>

// Initialize all Systems
void CSystem::InitSubsystems() {
#ifdef _DEBUG
	std::clog << "Initating all Systems" << std::endl;
#endif

	g_InputSystem.Init();
}

// Update all Systems
void CSystem::UpdateSubsystems() {
	// Gets called every frame
}

// Shutdown all Systems
void CSystem::ShutdownSubsystems() {
#ifdef _DEBUG
	std::clog << "Shutting Down all Systems" << std::endl;
#endif

	g_InputSystem.Shutdown();
}

void CSystem::SendEventToSubsystems()
{
}
