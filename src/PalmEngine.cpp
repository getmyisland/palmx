#include "SystemManager.h"

#include <iostream>

int main() {
	std::clog << "Starting PalmEngine..." << std::endl;

	SystemManager::GetInstance().InitSystems();

	SystemManager::GetInstance().UpdateSystems();

	return 0;
}