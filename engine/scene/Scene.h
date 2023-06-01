#ifndef _PE_SCENE_H__
#define _PE_SCENE_H__

#include <entity/Entity.h>
#include <entity/components/Camera.h>

#include <string>
#include <vector>

namespace PalmEngine
{
	class Scene
	{
	public:
		Scene(std::string name);		
		~Scene();

	private:
		Scene();

	public:
		std::string GetName() const;

		Camera* GetMainCamera();
		void SetMainCamera(Camera& mainCamera);

		std::vector<Entity*> GetEntitiesInScene() const;
		void AddEntityToScene(Entity& entity);
		void RemoveEntityFromScene(Entity& entity);

		void OnLoad();
		void OnUnload();

	private:
		const std::string _name;

		Camera* _mainCamera = nullptr;
		std::vector<Entity*> _entitiesInScene;
	};
}

#endif