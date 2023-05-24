#include "Entity.h"

namespace PalmEngine
{
	//-----------------------------------------------------------------------

	Entity::Entity() : _name("Entity")
	{
	
	}

	Entity::Entity(std::string name, Entity* parent, glm::vec3 position, glm::vec3 scale) : _name(name)
	{
		_parent = parent;
		_localPosition = position;
		_localScale = scale;
	}

	Entity::~Entity() {}

	//-----------------------------------------------------------------------

	std::string Entity::GetName() const
	{
		return _name;
	}

	//-----------------------------------------------------------------------

	glm::vec3 Entity::GetLocalPosition() const
	{
		return _localPosition;
	}

	void Entity::SetLocalPosition(glm::vec3 localPosition)
	{
		_localPosition = localPosition;
	}

	glm::vec3 Entity::GetGlobalPosition() const
	{
		glm::vec3 globalPosition = _localPosition;
		
		Entity* parent = _parent;
		while (parent != nullptr)
		{
			globalPosition += parent->GetLocalPosition();
			parent = parent->_parent;
		}

		return globalPosition;
	}

	void Entity::SetGlobalPosition(glm::vec3 globalPosition)
	{

	}

	glm::vec3 Entity::GetLocalScale() const
	{
		return _localScale;
	}

	void Entity::SetLocalScale(glm::vec3 localScale)
	{
		_localScale = localScale;
	}

	glm::vec3 Entity::GetGlobalScale() const
	{
		glm::vec3 globalScale = _localScale;

		Entity* parent = _parent;
		while (parent != nullptr)
		{
			globalScale += parent->GetLocalScale();
			parent = parent->_parent;
		}

		return globalScale;
	}

	void Entity::SetGlobalScale(glm::vec3 globalScale)
	{

	}

	//-----------------------------------------------------------------------

	Entity* Entity::GetParent() const
	{
		return _parent;
	}

	void Entity::SetParent(Entity* parent)
	{
		_parent->RemoveChild(*this);

		_parent = parent;

		parent->AddChild(*this);
	}

	std::vector<Entity*> Entity::GetChildren() const
	{
		return _children;
	}

	void Entity::AddChild(Entity& child)
	{
		_children.push_back(&child);
	}

	void Entity::RemoveChild(Entity& child)
	{
		_children.erase(std::remove(_children.begin(), _children.end(), &child), _children.end());
	}

	//-----------------------------------------------------------------------

	Model* Entity::GetModel() const
	{
		return _model;
	}

	void Entity::SetModel(Model& model)
	{
		_model = &model;
	}
}