#pragma once

#include "../InputSystem/InputListener.h"

class AppSystem : public InputListener {
public:
	AppSystem() {};
	~AppSystem() {};

	void Init();
	void Update();

	// InputListener
	void OnKeyDown(int key);
	void OnKeyUp(int key);
};