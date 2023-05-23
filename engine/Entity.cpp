#include "Entity.h"

namespace PalmEngine
{
	Entity::Entity() {}

	Entity::Entity(std::string name, Entity* parent, glm::vec3 position, glm::vec3 scale)
	{
		mName = name;
		mParent = parent;
		mLocalPosition = position;
		mLocalScale = scale;
	}

	Entity::~Entity() {}

	//-----------------------------------------------------------------------

	glm::vec3 Entity::GetGlobalPosition()
	{
		glm::vec3 globalPosition = mLocalPosition;
		
		Entity* parent = mParent;
		while (parent != nullptr)
		{
			globalPosition += parent->mLocalPosition;
			parent = parent->mParent;
		}

		return globalPosition;
	}

	glm::vec3 Entity::GetGlobalScale()
	{
		glm::vec3 globalScale = mLocalScale;

		Entity* parent = mParent;
		while (parent != nullptr)
		{
			globalScale += parent->mLocalScale;
			parent = parent->mParent;
		}

		return globalScale;
	}
}