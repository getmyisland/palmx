#ifndef _PALM_ENGINE_MANAGER_H__
#define _PALM_ENGINE_MANAGER_H__

namespace PalmEngine
{
	class PalmEngineManager
	{
		virtual void StartUp() = 0;
		virtual void ShutDown() = 0;
	};
}

#endif