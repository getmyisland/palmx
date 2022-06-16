#include "InputSystem.h"
#include <Windows.h>

InputSystem& InputSystem::GetInstance() {
	static InputSystem instance;

	return instance;
}

void InputSystem::AddListener(InputListener* inputListener) {

	// Add listener to the map
	mapListeners.insert(std::make_pair<InputListener*, InputListener*>
		(std::forward<InputListener*>(inputListener), std::forward<InputListener*>(inputListener)));
}

void InputSystem::RemoveListener(InputListener* inputListener) {

	// Check if listener exists in the map
	std::map<InputListener*, InputListener*>::iterator it = mapListeners.find(inputListener);

	// If it exists remove it
	if (it != mapListeners.end()) {
		mapListeners.erase(it);
	}
}

void InputSystem::UpdateInput() {

	if (::GetKeyboardState(keysState)) {

		for (unsigned int i = 0; i < 256; i++) {

			if (keysState[i] & 0x80) { //Key is down

				std::map<InputListener*, InputListener*>::iterator it = mapListeners.begin();

				while (it != mapListeners.end()) {
					it->second->OnKeyDown(i);
					it++;
				}
			}
			else { // Key is up
				if (keysState[i] != oldKeysState[i]) {

					std::map<InputListener*, InputListener*>::iterator it = mapListeners.begin();

					while (it != mapListeners.end()) {
						it->second->OnKeyUp(i);
						it++;
					}
				}
			}

			::memcpy(oldKeysState, keysState, sizeof(unsigned char) * 256);
		}
	}
}