#ifndef ISYSTEM_H
#define ISYSTEM_H
#ifdef _WIN32
#pragma once
#endif

#include "CSystemEvent.h"

class ISystem {
	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Shutdown() = 0;
	virtual void OnEvent(CSystemEvent i_CSystemEvent) = 0;
};

#endif // ISYSTEM_H