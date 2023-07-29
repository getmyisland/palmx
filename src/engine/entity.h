#ifndef PALMX_ENTITY_H
#define PALMX_ENTITY_H

#include <bitset>

namespace palmx
{
	extern int component_counter;
	template <class T>
	int GetComponentId()
	{
		static int component_id = component_counter++;
		return component_id;
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

	const int max_components = 32;
	const int max_entities = 100;
	typedef std::bitset<max_components> ComponentMask;

	struct Entity
	{
		EntityID id;
		ComponentMask component_mask;
	};

	class ComponentPool
	{
	public:
		ComponentPool(size_t element_size)
		{
			// Allocate enough memory to hold the max number of components, each with element size
			element_size_ = element_size;
			data_ = new char[element_size_ * max_components];
		}

		~ComponentPool()
		{
			delete[] data_;
		}

		inline void* Get(size_t index)
		{
			// Looking up the component at the desired index
			return data_ + index * element_size_;
		}

	private:
		ComponentPool() {}

		char* data_{ nullptr };
		size_t element_size_{ 0 };
	};
}

#endif