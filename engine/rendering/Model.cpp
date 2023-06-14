#include <glad/glad.h> // Needs to be imported first

#include "Model.h"

#include <debug/LogManager.h>

#ifndef STBI_INCLUDE_STB_IMAGE_H
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>
#endif

namespace palmx
{
	unsigned int TextureFromFile(std::string path, const std::string& directory);

	Model::Model(std::string path)
	{
		LoadModel(path);
	}

	Model::~Model() {}

	const std::vector<Mesh> Model::GetMeshes() const
	{
		return _meshes;
	}

	void Model::LoadModel(std::string path)
	{
		Assimp::Importer importer;
		const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		{
			auto error = importer.GetErrorString();
			DEBUG_LOG_ERROR(std::string("ASSIMP::") + error);
			return;
		}
		_directory = path.substr(0, path.find_last_of('/'));

		ProcessNode(scene->mRootNode, scene);
	}

	void Model::ProcessNode(aiNode* node, const aiScene* scene)
	{
		// Process all the node's meshes (if any)
		for (unsigned int i = 0; i < node->mNumMeshes; i++)
		{
			aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
			_meshes.push_back(ProcessMesh(mesh, scene));
		}
		// Then do the same for each of its children
		for (unsigned int i = 0; i < node->mNumChildren; i++)
		{
			ProcessNode(node->mChildren[i], scene);
		}
	}

	Mesh palmx::Model::ProcessMesh(aiMesh* mesh, const aiScene* scene)
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
			vertex.mPosition = vector;

			vector.x = mesh->mNormals[i].x;
			vector.y = mesh->mNormals[i].y;
			vector.z = mesh->mNormals[i].z;
			vertex.mNormal = vector;

			if (mesh->mTextureCoords[0]) // Does the mesh contain texture coordinates?
			{
				glm::vec2 vec;
				vec.x = mesh->mTextureCoords[0][i].x;
				vec.y = mesh->mTextureCoords[0][i].y;
				vertex.mTexCoords = vec;
			}
			else
				vertex.mTexCoords = glm::vec2(0.0f, 0.0f);

			vertices.push_back(vertex);
		}

		// Process indices
		for (unsigned int i = 0; i < mesh->mNumFaces; i++)
		{
			aiFace face = mesh->mFaces[i];
			for (unsigned int j = 0; j < face.mNumIndices; j++)
				indices.push_back(face.mIndices[j]);
		}

		// Create textures
		std::string materialName = scene->mMaterials[mesh->mMaterialIndex]->GetName().C_Str();
		Texture albedoTexture;
		albedoTexture.mID = TextureFromFile(std::string(materialName + "_texture_albedo.jpg"), _directory);
		Texture normalTexture;
		normalTexture.mID = TextureFromFile(std::string(materialName + "_texture_normal.jpg"), _directory);

		return Mesh(vertices, indices, albedoTexture, normalTexture);
	}

	unsigned int TextureFromFile(std::string path, const std::string& directory)
	{
		std::string filename = std::string(path);
		filename = directory + '/' + filename;
		unsigned int textureID;
		glGenTextures(1, &textureID);

		int width, height, nrComponents;
		unsigned char* data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
		if (data)
		{
			GLenum format = GL_RGB;
			if (nrComponents == 1)
				format = GL_RED;
			else if (nrComponents == 3)
				format = GL_RGB;
			else if (nrComponents == 4)
				format = GL_RGBA;

			glBindTexture(GL_TEXTURE_2D, textureID);
			glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			stbi_image_free(data);
		}
		else
		{
			DEBUG_LOG_ERROR("Texture failed to load at path: " + std::string(filename));
			stbi_image_free(data);
		}

		return textureID;
	}
}