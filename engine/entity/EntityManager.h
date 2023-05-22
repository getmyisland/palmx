#ifndef _PE_ENTITY_MANAGER_H__
#define _PE_ENTITY_MANAGER_H__

#include <PalmEngineSingleton.h>
#include <PalmEngineManager.h>

namespace PalmEngine
{
	class EntityManager : PalmEngineManager, public PalmEngineSingleton<EntityManager>
	{
	public:
		EntityManager();
		~EntityManager();

		static EntityManager& GetSingleton(void);
		static EntityManager* GetSingletonPtr(void);

		virtual void StartUp() override;
		virtual void ShutDown() override;
	};
}

#endif