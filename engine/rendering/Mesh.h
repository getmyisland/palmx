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
		glm::vec3 m_Position;
		glm::vec3 m_Normal;
		glm::vec2 m_TexCoords;
		glm::vec3 m_Tangent;
		glm::vec3 m_Bitangent;
		int m_BoneIDs[MAX_BONE_INFLUENCE];
		float m_Weights[MAX_BONE_INFLUENCE];
	};

	struct Texture
	{
		unsigned int m_ID = 0;
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