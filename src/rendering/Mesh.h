#ifndef PALMX_MESH_H_
#define PALMX_MESH_H_

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <memory>
#include <string>
#include <vector>

#define MAX_BONE_INFLUENCE 4

namespace palmx
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
		std::string mName;
		unsigned int mID;
	};

	class Mesh
	{
	public:
		Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, const std::shared_ptr<Texture> albedoTexture, const std::shared_ptr<Texture> normalTexture);
		~Mesh();

		const std::vector<Vertex> GetVertices() const;
		const std::vector<unsigned int> GetIndices() const;
		const std::shared_ptr<Texture> GetAlbedoTexture() const;
		const std::shared_ptr<Texture> GetNormalTexture() const;

		const unsigned int GetVAO() const;

	private:
		Mesh();

		std::vector<Vertex>       _vertices;
		std::vector<unsigned int> _indices;
		std::shared_ptr<Texture> _albedoTexture;
		std::shared_ptr<Texture> _normalTexture;

		unsigned int _vao = 0;
		unsigned int _vbo = 0;
		unsigned int _ebo = 0;

		void SetupMesh();
	};
}

#endif