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
		Entity(std::string name, Entity* parent, glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f));
		~Entity();

	private:
		Entity();

	public:
		std::string GetName() const;

		glm::vec3 GetLocalPosition() const;
		void SetLocalPosition(glm::vec3 localPosition);

		glm::vec3 GetGlobalPosition() const;
		void SetGlobalPosition(glm::vec3 globalPosition);

		glm::vec3 GetLocalScale() const;
		void SetLocalScale(glm::vec3 localScale);

		glm::vec3 GetGlobalScale() const;
		void SetGlobalScale(glm::vec3 globalScale);

		Entity* GetParent() const;
		void SetParent(Entity* parent);

		std::vector<Entity*> GetChildren() const;
		void AddChild(Entity& child);
		void RemoveChild(Entity& child);

		Model* GetModel() const;
		void SetModel(Model& model);

	private:
		const std::string _name;

		glm::vec3 _localPosition = glm::vec3(0.0f, 0.0f, 0.0f);
		glm::vec3 _localScale = glm::vec3(1.0f, 1.0f, 1.0f);

		Entity* _parent = nullptr;
		std::vector<Entity*> _children;

		Model* _model = nullptr;
	};
}

#endif