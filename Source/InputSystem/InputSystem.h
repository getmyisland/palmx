#pragma once

#include "InputListener.h"
#include <unordered_set>

class InputSystem
{
public:
	InputSystem() {};
	~InputSystem() {};

	void Update();
	void AddListener(InputListener* inputListener);
	void RemoveListener(InputListener* inputListener);

private:
	std::unordered_set<InputListener*> setListeners;
	unsigned char keysState[256] = {};
	unsigned char oldKeysState[256] = {};
};