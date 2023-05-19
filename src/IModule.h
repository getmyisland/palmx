#ifndef I_MODULE_H
#define I_MODULE_H

#include "ModuleManager.h"

class IModule
{
	virtual void Init() = 0;
	virtual void Shutdown() = 0;
};

#endif