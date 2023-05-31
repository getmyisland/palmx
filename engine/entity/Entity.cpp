#include "Entity.h"

namespace PalmEngine
{
	Entity::Entity(std::string name) : _name(name), _transform(Transform())
	{
		
	}

	Entity::~Entity() {}

	void Entity::Update()
	{
		for (auto& scriptBehavior : _scriptBehaviors)
		{
			if (scriptBehavior != nullptr)
			{
				scriptBehavior->Update();
			}
		}
	}

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

	void Entity::AddScriptBehavior(ScriptBehavior& scriptBehavior)
	{
		_scriptBehaviors.push_back(&scriptBehavior);
	}
	
	void Entity::RemoveScriptBehavior(ScriptBehavior& scriptBehavior)
	{
		// TODO
	}

	void Entity::SetRenderer(Renderer* renderer)
	{
		_renderer = renderer;
	}
}