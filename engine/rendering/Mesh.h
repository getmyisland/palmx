#ifndef _PE_MESH_H__
#define _PE_MESH_H__

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Shader.h"

#include <memory>
#include <string>
#include <vector>

#define MAX_BONE_INFLUENCE 4

namespace PalmEngine
{
	struct Vertex {
		// position
		glm::vec3 mPosition;
		// normal
		glm::vec3 mNormal;
		// texCoords
		glm::vec2 mTexCoords;
		// tangent
		glm::vec3 mTangent;
		// bitangent
		glm::vec3 mBitangent;
		//bone indexes which will influence this vertex
		int mBoneIDs[MAX_BONE_INFLUENCE];
		//weights from each bone
		float mWeights[MAX_BONE_INFLUENCE];
	};

	//-----------------------------------------------------------------------

	class Mesh
	{
	public:
		Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, Material* material);
		~Mesh();

	private:
		Mesh();

	public:
		// Mesh Data
		std::vector<Vertex>       mVertices;
		std::vector<unsigned int> mIndices;
		std::unique_ptr<Material> mMaterial;

		unsigned int mVAO;

		void Draw(glm::vec3 position, glm::vec3 scale);

	private:
		// Render Data 
		unsigned int _VBO, _EBO;

		void SetupMesh();
	};
}

#endif