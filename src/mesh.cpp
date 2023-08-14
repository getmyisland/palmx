#include <glad/glad.h> // Needs to be included first

#include <palmx/mesh.h>

namespace palmx::render
{
	Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, const std::shared_ptr<Texture> albedo_texture, const std::shared_ptr<Texture> normal_texture)
		: albedo_texture_(albedo_texture), normal_texture_(normal_texture)
	{
		vertices_ = vertices;
		indices_ = indices;

		SetupMesh();
	}

	Mesh::~Mesh()
	{

	}

	const std::vector<Vertex> Mesh::GetVertices() const
	{
		return vertices_;
	}

	const std::vector<unsigned int> Mesh::GetIndices() const
	{
		return indices_;
	}

	const std::shared_ptr<Texture> Mesh::GetAlbedoTexture() const
	{
		return albedo_texture_;
	}

	const std::shared_ptr<Texture> Mesh::GetNormalTexture() const
	{
		return normal_texture_;
	}

	const unsigned int Mesh::GetVAO() const
	{
		return vao_;
	}

	void Mesh::SetupMesh()
	{
		// Create buffers/arrays
		glGenVertexArrays(1, &vao_);
		glGenBuffers(1, &vbo_);
		glGenBuffers(1, &ebo_);

		glBindVertexArray(vao_);
		// Load data into vertex buffers
		glBindBuffer(GL_ARRAY_BUFFER, vbo_);
		// A great thing about structs is that their memory layout is sequential for all its items.
		// The effect is that we can simply pass a pointer to the struct and it translates perfectly to a glm::vec3/2 array which
		// Again translates to 3/2 floats which translates to a byte array.
		glBufferData(GL_ARRAY_BUFFER, vertices_.size() * sizeof(Vertex), &vertices_[0], GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_.size() * sizeof(unsigned int), &indices_[0], GL_STATIC_DRAW);

		// Set the vertex attribute pointers
		// Vertex Positions
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
		// Vertex normals
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
		// Vertex texture coords
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, tex_coords));
		// Vertex tangent
		glEnableVertexAttribArray(3);
		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, tangent));
		// Vertex bitangent
		glEnableVertexAttribArray(4);
		glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, bitangent));
		// IDs
		glEnableVertexAttribArray(5);
		glVertexAttribIPointer(5, 4, GL_INT, sizeof(Vertex), (void*)offsetof(Vertex, bone_ids));
		// Weights
		glEnableVertexAttribArray(6);
		glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, weights));
		glBindVertexArray(0);
	}
}