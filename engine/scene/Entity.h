#ifndef _PE_ENTITY_H__
#define _PE_ENTITY_H__

#define INVALID_ENTITY PalmEngine::CreateEntityId(EntityIndex(-1), 0)

#include <bitset>

namespace PalmEngine
{
	extern int s_ComponentCounter;
	template <class T>
	int GetComponentId()
	{
		static int s_ComponentId = s_ComponentCounter++;
		return s_ComponentId;
	}

	typedef unsigned int EntityIndex;
	typedef unsigned int EntityVersion;
	typedef unsigned long long EntityID;

	inline EntityID CreateEntityId(EntityIndex index, EntityVersion version)
	{
		// Shift the index up 32, and put the version in the bottom
		return ((EntityID)index << 32) | ((EntityID)version);
	}
	inline EntityIndex GetEntityIndex(EntityID id)
	{
		// Shift down 32 so we lose the version and get our index
		return id >> 32;
	}
	inline EntityVersion GetEntityVersion(EntityID id)
	{
		// Cast to a 32 bit int to get our version number (loosing the top 32 bits)
		return (EntityVersion)id;
	}
	inline bool IsEntityValid(EntityID id)
	{
		// Check if the index is our invalid index
		return (id >> 32) != EntityIndex(-1);
	}

	const int MAX_COMPONENTS = 32;
	const int MAX_ENTITIES = 100;
	typedef std::bitset<MAX_COMPONENTS> ComponentMask;

	struct Entity
	{
		EntityID m_ID;
		ComponentMask m_ComponentMask;
	};

	struct ComponentPool
	{
		ComponentPool(size_t elementSize)
		{
			// We'll allocate enough memory to hold MAX_ENTITIES, each with element size
			_elementSize = elementSize;
			_pData = new char[_elementSize * MAX_ENTITIES];
		}

		~ComponentPool()
		{
			delete[] _pData;
		}

		inline void* Get(size_t index)
		{
			// looking up the component at the desired index
			return _pData + index * _elementSize;
		}

	private:
		ComponentPool() {}

		char* _pData{ nullptr };
		size_t _elementSize{ 0 };
	};
}

#endif