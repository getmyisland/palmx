#include "SystemManager.h"

#include <iostream>

void SystemManager::InitSystems() {
#ifdef _DEBUG
	std::clog << "Initating all Systems" << std::endl;
#endif
}

void SystemManager::UpdateSystems() {
	
}

void SystemManager::ShutDownSystems() {
#ifdef _DEBUG
	std::clog << "Shutting Down all Systems" << std::endl;
#endif
}

void SystemManager::SendMessageEventToQueue(Message message) {
#ifdef _DEBUG
	std::clog << "Event " << message.getEventName(message.getMessageEvent()) << " was called." << std::endl;
#endif

	g_MessageSystem.SendMessageToQueue(message);
}

void SystemManager::NotifyMessageSystem() {
#ifdef _DEBUG
	std::clog << "Notify Systems" << std::endl;
#endif

	g_MessageSystem.Notify();
}