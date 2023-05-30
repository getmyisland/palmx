#ifndef _PE_MODEL_H__
#define _PE_MODEL_H__

#include "Mesh.h"

#include <memory>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace PalmEngine
{
	class Model
	{
	public:
		Model(std::string path);
		~Model();

		const std::vector<Mesh> GetMeshes() const;

	private:
		Model();

		std::vector<Mesh> _meshes;
		std::string _directory;

		void LoadModel(std::string path);
		void ProcessNode(aiNode* node, const aiScene* scene);
		Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);
	};
}

#endif