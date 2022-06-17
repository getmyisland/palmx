#include "InputSystem.h"
#include <Windows.h>
#include <iostream>

void InputSystem::AddListener(InputListener* inputListener) {

	// Add new Listener
	setListeners.insert(inputListener);

	std::clog << "Added new Input Listener" << std::endl;
}

void InputSystem::RemoveListener(InputListener* inputListener) {

	// Check if listener exists in the set and remove it
	if (setListeners.find(inputListener) != setListeners.end()) {
		setListeners.erase(inputListener);

		std::clog << "Removed existing Input Listener" << std::endl;
	}
}

void InputSystem::Update() {

	if (::GetKeyboardState(keysState)) {

		for (unsigned int i = 0; i < 256; i++) {

			if (keysState[i] & 0x80) { //Key is down

				std::unordered_set<InputListener*>::iterator it = setListeners.begin();

				while (it != setListeners.end()) {
					(*it)->OnKeyDown(i);
					++it;
				}
			}
			else { // Key is up
				if (keysState[i] != oldKeysState[i]) {

					std::unordered_set<InputListener*>::iterator it = setListeners.begin();

					while (it != setListeners.end()) {
						(*it)->OnKeyUp(i);
						++it;
					}
				}
			}

			::memcpy(oldKeysState, keysState, sizeof(unsigned char) * 256);
		}
	}
}