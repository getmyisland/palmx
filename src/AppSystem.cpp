#include "InputSystem.cpp"

class AppSystem {
public:
	AppSystem() {};
	~AppSystem() {};

	// List of active systems
	InputSystem gInputSystem;

	void initApp() {
		// Init all subsystems
		gInputSystem.init();

		// Start the main game loop
		updateApp();

		// Close the app
		shutDownApp();
	}

private:
	bool isGameRunning = true;

	void updateApp() {
		while (isGameRunning) {

		}
	}

	void shutDownApp() {
		//Shutdown all subsystems
		gInputSystem.shutDown();
	}
};