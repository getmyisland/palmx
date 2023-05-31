#ifndef _PE_ENTITY_H__
#define _PE_ENTITY_H__

#include <entity/ScriptBehavior.h>
#include <entity/Transform.h>
#include <rendering/Renderer.h>

namespace PalmEngine
{
	class Entity
	{
	public:
		Entity(std::string name = "New Entity");
		~Entity();

		void Update();
		void Render() const;

		std::string GetName() const;
		const Transform* GetTransform();

		void AddScriptBehavior(ScriptBehavior& scriptBehavior);
		void RemoveScriptBehavior(ScriptBehavior& scriptBehavior);
		void SetRenderer(Renderer* renderer);

	private:
		const std::string _name;

		// Required components
		const Transform _transform;

		// Optional components
		std::vector<ScriptBehavior*> _scriptBehaviors = std::vector<ScriptBehavior*>(); // Using ptrs here may be risky
		Renderer* _renderer = nullptr;
	};
}

#endif