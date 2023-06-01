#ifndef _PE_ENTITY_H__
#define _PE_ENTITY_H__

#include <entity/components/ScriptBehavior.h>
#include <entity/components/Camera.h>
#include <entity/components/Transform.h>
#include <rendering/Renderer.h>

namespace PalmEngine
{
	class Entity
	{
	public:
		Entity(std::string name = "New Entity");
		~Entity();

		void Update(float deltaTime);
		void Render(Camera* camera) const;

		std::string GetName() const;
		Transform* GetTransform();

		void AddScriptBehavior(ScriptBehavior& scriptBehavior);
		void RemoveScriptBehavior(ScriptBehavior& scriptBehavior);
		void SetCamera(Camera& camera);
		void SetRenderer(Renderer& renderer);

	private:
		const std::string _name;

		// Required components
		Transform _transform;

		// Optional components
		std::vector<ScriptBehavior*> _scriptBehaviors = std::vector<ScriptBehavior*>();
		Camera* _camera = nullptr;
		Renderer* _renderer = nullptr;
	};
}

#endif