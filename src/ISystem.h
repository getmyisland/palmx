#pragma once

#include "SystemEvent.h"

class ISystem {
	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Shutdown() = 0;
	virtual void OnEvent(SystemEvent i_SysEvent) = 0;
};