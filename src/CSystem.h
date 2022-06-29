#pragma once

#include "InputSystem/CInputSystem.h"

class CSystem {
public:
	static CSystem& getInstance() {
		static CSystem    instance; // Guaranteed to be destroyed.
							  // Instantiated on first use.
		return instance;
	};

	void InitSubsystems();
	void UpdateSubsystems();
	void ShutdownSubsystems();
	void SendEventToSubsystems();

private:
	CSystem() {};

	// Subsystems
	CInputSystem g_InputSystem;

public:
	CSystem(CSystem const&) = delete;
	void operator=(CSystem const&) = delete;
};