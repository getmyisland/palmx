#include "SystemManager.h"

void SystemManager::InitSystems() {
	gAppSystem.Init();
}

void SystemManager::UpdateSystems() {
	while (isGameRunning) {
		gAppSystem.Update();
		gInputSystem.Update();
	}
}

void SystemManager::ShutDownSystems() {
	
}