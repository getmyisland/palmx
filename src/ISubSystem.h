#pragma once

#include "SystemEvent.h"

__interface ISubsystem {
public:
	// Pure virtual methods for every subsystem to implement
	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Shutdown() = 0;
	virtual void OnEvent(SystemEvent sysEvent) = 0;
};