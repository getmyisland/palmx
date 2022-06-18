#include "SystemManager.h"

void SystemManager::InitSystems() {

}

void SystemManager::UpdateSystems() {
	
}

void SystemManager::ShutDownSystems() {
	
}

void SystemManager::SendMessageEvent(Message message) {
	gMessageSystem.SendMessageToQueue(message);
	gMessageSystem.Notify();
}