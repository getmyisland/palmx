#include <glad/glad.h> // Needs to be included first

#include "mesh.h"

namespace palmx
{
	Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, const std::shared_ptr<Texture> albedoTexture, const std::shared_ptr<Texture> normalTexture)
		: _albedoTexture(albedoTexture), _normalTexture(normalTexture)
	{
		_vertices = vertices;
		_indices = indices;

		SetupMesh();
	}

	Mesh::~Mesh()
	{

	}

	const std::vector<Vertex> Mesh::GetVertices() const
	{
		return _vertices;
	}

	const std::vector<unsigned int> Mesh::GetIndices() const
	{
		return _indices;
	}

	const std::shared_ptr<Texture> Mesh::GetAlbedoTexture() const
	{
		return _albedoTexture;
	}

	const std::shared_ptr<Texture> Mesh::GetNormalTexture() const
	{
		return _normalTexture;
	}

	const unsigned int Mesh::GetVAO() const
	{
		return _vao;
	}

	void Mesh::SetupMesh()
	{
		// Create buffers/arrays
		glGenVertexArrays(1, &_vao);
		glGenBuffers(1, &_vbo);
		glGenBuffers(1, &_ebo);

		glBindVertexArray(_vao);
		// Load data into vertex buffers
		glBindBuffer(GL_ARRAY_BUFFER, _vbo);
		// A great thing about structs is that their memory layout is sequential for all its items.
		// The effect is that we can simply pass a pointer to the struct and it translates perfectly to a glm::vec3/2 array which
		// Again translates to 3/2 floats which translates to a byte array.
		glBufferData(GL_ARRAY_BUFFER, _vertices.size() * sizeof(Vertex), &_vertices[0], GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indices.size() * sizeof(unsigned int), &_indices[0], GL_STATIC_DRAW);

		// Set the vertex attribute pointers
		// Vertex Positions
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
		// Vertex normals
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, mNormal));
		// Vertex texture coords
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, mTexCoords));
		// Vertex tangent
		glEnableVertexAttribArray(3);
		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, mTangent));
		// Vertex bitangent
		glEnableVertexAttribArray(4);
		glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, mBitangent));
		// IDs
		glEnableVertexAttribArray(5);
		glVertexAttribIPointer(5, 4, GL_INT, sizeof(Vertex), (void*)offsetof(Vertex, mBoneIDs));
		// Weights
		glEnableVertexAttribArray(6);
		glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, mWeights));
		glBindVertexArray(0);
	}
}