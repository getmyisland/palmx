#include <iostream>

// Include all Manager
#include "SimulationManager.cpp"

int main() {
	// Create Singletons
	SimulationManager gSimulationManager;

	// Startup all Manager

	// Start the game loop
	gSimulationManager.run();

	// Shutdown all Manager

	return 0;
}