#include "Entity.h"

namespace PalmEngine
{
	Entity::Entity(std::string name) : _name(name), _transform(Transform())
	{
		
	}

	Entity::~Entity() {}

	void Entity::Update(float deltaTime)
	{
		for (auto& scriptBehavior : _scriptBehaviors)
		{
			if (scriptBehavior != nullptr)
			{
				scriptBehavior->Update(deltaTime, _transform);
			}
		}
	}

	void Entity::Render(Camera* camera) const
	{
		if (_renderer != nullptr)
		{
			_renderer->Render(camera, _transform);
		}
	}

	std::string Entity::GetName() const
	{
		return _name;
	}

	Transform* Entity::GetTransform()
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

	void Entity::SetCamera(Camera& camera)
	{
		_camera = &camera;
	}

	void Entity::SetRenderer(Renderer& renderer)
	{
		_renderer = &renderer;
	}
}