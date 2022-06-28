#include "ISystem.h"

#include <iostream>

// Initialize all Systems
void ISystem::InitSystems() {
#ifdef _DEBUG
	std::clog << "Initating all Systems" << std::endl;
#endif

	g_InputSystem.Init();
}

// Update all Systems
void ISystem::UpdateSystems() {
	// Gets called every frame
}

// Shutdown all Systems
void ISystem::ShutDownSystems() {
#ifdef _DEBUG
	std::clog << "Shutting Down all Systems" << std::endl;
#endif

	g_InputSystem.ShutDown();
}

// Send a Message Event to the Queue of the MessageSystem
void ISystem::SendMessageEventToQueue(Message message) {
#ifdef _DEBUG
	std::clog << "Event " << message.getEventName(message.getMessageEvent()) << " was called" << std::endl;
#endif

	g_MessageSystem.SendMessageToQueue(message);
}

// Work trough all Messages in the Message Queue
void ISystem::NotifyMessageNodes() {
#ifdef _DEBUG
	std::clog << "Notify All Message System Nodes" << std::endl;
#endif

	g_MessageSystem.Notify();
}