#ifndef _PE_ENTITY_H__
#define _PE_ENTITY_H__

#include <entity/Transform.h>
#include <rendering/Renderer.h>

namespace PalmEngine
{
	class Entity
	{
	public:
		Entity(std::string name = "New Entity");
		~Entity();

		void Render() const;

		std::string GetName() const;
		const Transform* GetTransform();

		void SetRenderer(Renderer* renderer);

	private:
		const std::string _name;

		// Required components
		const Transform _transform;

		// Optional components
		Renderer* _renderer = nullptr;
	};
}

#endif