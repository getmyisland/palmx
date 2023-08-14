#ifndef PALMX_RENDER_MESH_H
#define PALMX_RENDER_MESH_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <memory>
#include <string>
#include <vector>

#define MAX_BONE_INFLUENCE 4

namespace palmx::render
{
	struct Vertex {
		glm::vec3 position;
		glm::vec3 normal;
		glm::vec2 tex_coords;
		glm::vec3 tangent;
		glm::vec3 bitangent;
		int bone_ids[MAX_BONE_INFLUENCE];
		float weights[MAX_BONE_INFLUENCE];
	};

	struct Texture
	{
		std::string name;
		unsigned int id;
	};

	class Mesh
	{
	public:
		Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, const std::shared_ptr<Texture> albedo_texture, const std::shared_ptr<Texture> normal_texture);
		~Mesh();

		const std::vector<Vertex> GetVertices() const;
		const std::vector<unsigned int> GetIndices() const;
		const std::shared_ptr<Texture> GetAlbedoTexture() const;
		const std::shared_ptr<Texture> GetNormalTexture() const;

		const unsigned int GetVAO() const;

	private:
		Mesh();

		std::vector<Vertex>       vertices_;
		std::vector<unsigned int> indices_;
		std::shared_ptr<Texture> albedo_texture_;
		std::shared_ptr<Texture> normal_texture_;

		unsigned int vao_ = 0;
		unsigned int vbo_ = 0;
		unsigned int ebo_ = 0;

		void SetupMesh();
	};
}

#endif