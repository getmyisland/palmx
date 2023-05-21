#ifndef _PE_I_MODULE_H__
#define _PE_I_MODULE_H__

#include "ModuleManager.h"

namespace PalmEngine
{
	class IModule
	{
		virtual void StartUp() = 0;
		virtual void ShutDown() = 0;
	};
}

#endif