#ifndef _PE_MODEL_H__
#define _PE_MODEL_H__

#include "Material.h"
#include "Mesh.h"
#include "Shader.h"

#include <memory>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace PalmEngine
{
	class Model
	{
	public:
		Model(std::string path, Shader& shader);
		~Model();

	private:
		Model();

	public:
		void Draw(glm::vec3 position, glm::vec3 scale);

	private:
		// Model Data
		std::vector<Mesh*> _meshes;
		std::string _directory;

		void LoadModel(std::string path, Shader& shader);
		void ProcessNode(Shader& shader, aiNode* node, const aiScene* scene);
		Mesh* ProcessMesh(Shader& shader, aiMesh* mesh, const aiScene* scene);
		Material CreateMaterial(Shader& shader, std::string materialName);
	};
}

#endif