#ifndef PALMX_ENTITY_H
#define PALMX_ENTITY_H

#include <bitset>

namespace palmx
{
	extern int sComponentCounter;
	template <class T>
	int GetComponentId()
	{
		static int sComponentId = sComponentCounter++;
		return sComponentId;
	}

	using EntityIndex = unsigned int;
	using EntityVersion = unsigned int;
	using EntityID = unsigned long long;

	inline EntityID CreateEntityId(EntityIndex index, EntityVersion version)
	{
		// Shift the index up 32, and put the version in the bottom
		return ((EntityID)index << 32) | ((EntityID)version);
	}
	inline EntityIndex GetEntityIndex(EntityID id)
	{
		// Shift down 32 bit to lose the version and get the index
		return id >> 32;
	}
	inline EntityVersion GetEntityVersion(EntityID id)
	{
		// Cast to a 32 bit int to get the version number (losing the top 32 bits)
		return (EntityVersion)id;
	}
	inline bool IsEntityValid(EntityID id)
	{
		// Check if the index is invalid
		return (id >> 32) != EntityIndex(-1);
	}

	const int MAX_COMPONENTS = 32;
	const int MAX_ENTITIES = 100;
	typedef std::bitset<MAX_COMPONENTS> ComponentMask;

	struct Entity
	{
		EntityID mId;
		ComponentMask mComponentMask;
	};

	struct ComponentPool
	{
		ComponentPool(size_t elementSize)
		{
			// Allocate enough memory to hold the max number of components, each with element size
			_elementSize = elementSize;
			_data = new char[_elementSize * MAX_COMPONENTS];
		}

		~ComponentPool()
		{
			delete[] _data;
		}

		inline void* Get(size_t index)
		{
			// Looking up the component at the desired index
			return _data + index * _elementSize;
		}

	private:
		ComponentPool() {}

		char* _data{ nullptr };
		size_t _elementSize{ 0 };
	};
}

#endif