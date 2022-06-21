#include "SystemManager.h"

#include <iostream>

// Initialize all Systems
void SystemManager::InitSystems() {
#ifdef _DEBUG
	std::clog << "Initating all Systems" << std::endl;
#endif
}

// Update all Systems
void SystemManager::UpdateSystems() {

}

// Shutdown all Systems
void SystemManager::ShutDownSystems() {
#ifdef _DEBUG
	std::clog << "Shutting Down all Systems" << std::endl;
#endif
}

// Send a Message Event to the Queue of the MessageSystem
void SystemManager::SendMessageEventToQueue(Message message) {
#ifdef _DEBUG
	std::clog << "Event " << message.getEventName(message.getMessageEvent()) << " was called." << std::endl;
#endif

	g_MessageSystem.SendMessageToQueue(message);
}

// Work trough all Messages in the Message Queue
void SystemManager::NotifyMessageSystem() {
#ifdef _DEBUG
	std::clog << "Notify Systems" << std::endl;
#endif

	g_MessageSystem.Notify();
}