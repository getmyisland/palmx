#pragma once

#include "InputListener.h"
#include <map>

class InputSystem
{
public:
	static inline InputSystem& GetInstance();

	inline void UpdateInput();
	inline void AddListener(InputListener* inputListener);
	inline void RemoveListener(InputListener* inputListener);

private:
	InputSystem() {};

	std::map<InputListener*, InputListener*> mapListeners;
	unsigned char keysState[256] = {};
	unsigned char oldKeysState[256] = {};

public:
	InputSystem(InputSystem const&) = delete;
	void operator=(InputSystem const&) = delete;
};