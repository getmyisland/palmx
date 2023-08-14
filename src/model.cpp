#include <glad/glad.h> // Needs to be imported first

#include <palmx/model.h>

#include <palmx/logger.h>
#include <palmx/resource_loader.h>

namespace palmx::render
{
	Model::Model(std::string path)
	{
		LoadModel(path);
	}

	Model::~Model() {}

	const std::vector<Mesh> Model::GetMeshes() const
	{
		return meshes_;
	}

	void Model::LoadModel(std::string path)
	{
		Assimp::Importer importer;
		const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		{
			auto error = importer.GetErrorString();
			LOG_ERROR(std::string("ASSIMP::") + error);
			return;
		}
		directory_ = path.substr(0, path.find_last_of('/'));

		ProcessNode(scene->mRootNode, scene);
	}

	void Model::ProcessNode(aiNode* node, const aiScene* scene)
	{
		// Process all the node's meshes (if any)
		for (unsigned int i = 0; i < node->mNumMeshes; i++)
		{
			aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
			meshes_.push_back(ProcessMesh(mesh, scene));
		}
		// Then do the same for each of its children
		for (unsigned int i = 0; i < node->mNumChildren; i++)
		{
			ProcessNode(node->mChildren[i], scene);
		}
	}

	Mesh palmx::render::Model::ProcessMesh(aiMesh* mesh, const aiScene* scene)
	{
		std::vector<Vertex> vertices;
		std::vector<unsigned int> indices;

		for (unsigned int i = 0; i < mesh->mNumVertices; i++)
		{
			Vertex vertex;

			// Process vertex positions, normals and texture coordinates
			glm::vec3 vector;
			vector.x = mesh->mVertices[i].x;
			vector.y = mesh->mVertices[i].y;
			vector.z = mesh->mVertices[i].z;
			vertex.position = vector;

			vector.x = mesh->mNormals[i].x;
			vector.y = mesh->mNormals[i].y;
			vector.z = mesh->mNormals[i].z;
			vertex.normal = vector;

			if (mesh->mTextureCoords[0]) // Does the mesh contain texture coordinates?
			{
				glm::vec2 vec;
				vec.x = mesh->mTextureCoords[0][i].x;
				vec.y = mesh->mTextureCoords[0][i].y;
				vertex.tex_coords = vec;
			}
			else
				vertex.tex_coords = glm::vec2(0.0f, 0.0f);

			vertices.push_back(vertex);
		}

		// Process indices
		for (unsigned int i = 0; i < mesh->mNumFaces; i++)
		{
			aiFace face = mesh->mFaces[i];
			for (unsigned int j = 0; j < face.mNumIndices; j++)
				indices.push_back(face.mIndices[j]);
		}

		// Create
		std::string material_name = scene->mMaterials[mesh->mMaterialIndex]->GetName().C_Str();
		std::shared_ptr<Texture> albedo_texture = ResourceLoader::LoadTexture(material_name + "_texture_albedo", std::string(directory_ + "/" + material_name + "_texture_albedo.jpg").c_str());
		std::shared_ptr<Texture> normal_texture = ResourceLoader::LoadTexture(material_name + "_texture_normal", std::string(directory_ + "/" + material_name + "_texture_normal.jpg").c_str());

		return Mesh(vertices, indices, albedo_texture, normal_texture);
	}
}