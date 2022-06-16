#include "SingletonManager.h"
#include <iostream>

class SimulationManager : public SingletonManager {
public:
	SimulationManager() {};
	~SimulationManager() {};

	void startUp() {};
	void shutDown() {};

	void run() {
		bool isGameRunning = true;
		int cnt = 0;

		while (isGameRunning) {
			if (cnt > 25) {
				break;
			}
			
			std::cout << "Game running..." << std::endl;

			cnt++;
		}
	}
};