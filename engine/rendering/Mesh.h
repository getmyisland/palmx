#ifndef _PE_MESH_H__
#define _PE_MESH_H__

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <string>
#include <vector>

#define MAX_BONE_INFLUENCE 4

namespace PalmEngine
{
	struct Vertex {
		glm::vec3 mPosition;
		glm::vec3 mNormal;
		glm::vec2 mTexCoords;
		glm::vec3 mTangent;
		glm::vec3 mBitangent;
		int mBoneIDs[MAX_BONE_INFLUENCE];
		float mWeights[MAX_BONE_INFLUENCE];
	};

	struct Texture
	{
		unsigned int mID = 0;
	};

	class Mesh
	{
	public:
		Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, const Texture& albedoTexture, const Texture& normalTexture);
		~Mesh();

		const std::vector<Vertex> GetVertices() const;
		const std::vector<unsigned int> GetIndices() const;
		const Texture& GetAlbedoTexture() const;
		const Texture& GetNormalTexture() const;

		const unsigned int GetVAO() const;

	private:
		Mesh();

		std::vector<Vertex>       _vertices;
		std::vector<unsigned int> _indices;
		const Texture _albedoTexture;
		const Texture _normalTexture;

		unsigned int _vao = 0;
		unsigned int _vbo = 0;
		unsigned int _ebo = 0;

		void SetupMesh();
	};
}

#endif