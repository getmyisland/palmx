#ifndef _PE_MESH_H__
#define _PE_MESH_H__

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Shader.h"

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
		Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, const Material& material);
		~Mesh();

	private:
		Mesh();

	public:
		void Draw(glm::vec3 position, glm::vec3 scale);

	private:
		// Mesh Data
		std::vector<Vertex>       _vertices;
		std::vector<unsigned int> _indices;
		Material _material;

		// Render Data 
		unsigned int mVAO = 0;
		unsigned int _VBO = 0;
		unsigned int _EBO = 0;

		void SetupMesh();
	};
}

#endif