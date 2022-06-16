#include "ISubsystem.h"
#include <iostream>

class InputSystem : public ISubsystem {
public:
	void init() {
		std::cout << "Init Input System" << std::endl;
	}

	void update() {

	}

	void shutDown() {
	
	}
};