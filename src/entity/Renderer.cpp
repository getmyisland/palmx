#include <glad/glad.h> // Needs to be included first

#include "Renderer.h"

#include <entity/Transform.h>
#include <rendering/Model.h>
#include <rendering/Shader.h>
#include <Root.h>

namespace palmx
{
	Renderer::Renderer() {}
	Renderer::~Renderer() {}

	void Renderer::Render(const std::shared_ptr<Shader> shader, const Transform& transform)
	{
		if (mModel == nullptr)
		{
			// Cannot render if there is no model
			return;
		}

		for (auto& mesh : mModel->GetMeshes())
		{
			// Render the mesh
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, transform.GetPosition());
			model = glm::scale(model, transform.GetScale());
			shader->SetMat4("model", model);

			glActiveTexture(GL_TEXTURE0 + 0);
			// Set the sampler to the correct texture unit
			glUniform1i(glGetUniformLocation(shader->mId, "texture_albedo"), 0);
			// Bind the texture
			glBindTexture(GL_TEXTURE_2D, mesh.GetAlbedoTexture()->mId);

			glActiveTexture(GL_TEXTURE0 + 1);
			// Set the sampler to the correct texture unit
			glUniform1i(glGetUniformLocation(shader->mId, "texture_normal"), 1);
			// Bind the texture
			glBindTexture(GL_TEXTURE_2D, mesh.GetNormalTexture()->mId);

			// Draw mesh
			glBindVertexArray(mesh.GetVAO());
			glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(mesh.GetIndices().size()), GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);

			// Set everything back to default
			glActiveTexture(GL_TEXTURE0);
		}
	}
}