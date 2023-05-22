#include "EntityManager.h"

namespace PalmEngine
{
	EntityManager::EntityManager() { }
	EntityManager::~EntityManager() { }

	//-----------------------------------------------------------------------

	template<> EntityManager* PalmEngineSingleton<EntityManager>::msSingleton = 0;
	EntityManager* EntityManager::GetSingletonPtr(void)
	{
		return msSingleton;
	}
	EntityManager& EntityManager::GetSingleton(void)
	{
		return (*msSingleton);
	}

	//-----------------------------------------------------------------------

	void PalmEngine::EntityManager::StartUp()
	{

	}

	void PalmEngine::EntityManager::ShutDown()
	{

	}
}