#ifndef _PE_ENTITY_MANAGER_H__
#define _PE_ENTITY_MANAGER_H__

#include <PalmEngineSingleton.h>
#include <PalmEngineManager.h>

namespace PalmEngine
{
	class EntityManager : PalmEngineManager, PalmEngineSingleton<EntityManager>
	{
	public:
		EntityManager();
		~EntityManager();

		virtual void StartUp() override;
		virtual void ShutDown() override;
	};
}

#endif