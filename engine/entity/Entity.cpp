#include "Entity.h"

namespace PalmEngine
{
	Entity::Entity(std::string name) : _name(name), _transform(Transform())
	{
		
	}

	Entity::~Entity() {}

	void Entity::Render() const
	{
		if (_renderer != nullptr)
		{
			_renderer->Render(_transform);
		}
	}

	std::string Entity::GetName() const
	{
		return _name;
	}

	const Transform* Entity::GetTransform()
	{
		return &_transform;
	}

	void Entity::SetRenderer(Renderer* renderer)
	{
		_renderer = renderer;
	}
}