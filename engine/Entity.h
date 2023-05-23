#ifndef _PE_ENTITY_H__
#define _PE_ENTITY_H__

#include <rendering/Model.h>

#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace PalmEngine
{
	class Entity
	{
	public:
		Entity(std::string name, Entity* parent, glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 scale = glm::vec3(0.0f, 0.0f, 0.0f));

		~Entity();

	private:
		Entity();

	public:
		std::string mName = "Entity";
		glm::vec3 mLocalPosition = glm::vec3(0.0f, 0.0f, 0.0f);
		glm::vec3 mLocalScale = glm::vec3(0.0f, 0.0f, 0.0f);
		
		Model* mModel = nullptr;

		Entity* mParent = nullptr;
		std::vector<Entity*> mChilds;

		glm::vec3 GetGlobalPosition();
		glm::vec3 GetGlobalScale();
	};
}

#endif