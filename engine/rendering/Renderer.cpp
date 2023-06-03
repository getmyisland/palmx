#include <glad/glad.h> // holds all OpenGL type declarations

#include "Renderer.h"
#include <PalmEngineRoot.h>

namespace PalmEngine
{
	Renderer::Renderer(const Model& model, const Shader& shader) : _model(model), _shader(shader)
	{

	}

	Renderer::~Renderer()
	{

	}

	void Renderer::Render(Camera* camera, const Transform& transform)
	{
		for (auto& mesh : _model.GetMeshes())
		{
			_shader.Use();

			// View/Projection Transformations
			glm::mat4 projection = glm::perspective(glm::radians(camera->GetZoom()), static_cast<float>(PalmEngineRoot::GetSingletonPtr()->mConfig->GetWidth()) / static_cast<float>(PalmEngineRoot::GetSingletonPtr()->mConfig->GetHeight()), 0.1f, 100.0f);
			_shader.SetMat4("projection", projection);

			glm::mat4 view = camera->GetViewMatrix();
			_shader.SetMat4("view", view);

			// Render the mesh
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, transform.mPosition);
			//model = glm::rotate(model, transform.mRotation); Currently deactivated because this requires a Quaternion which is yet to be implemented
			model = glm::scale(model, transform.mScale);
			_shader.SetMat4("model", model);

			glActiveTexture(GL_TEXTURE0 + 0);
			// Set the sampler to the correct texture unit
			glUniform1i(glGetUniformLocation(_shader.mID, "texture_albedo"), 0);
			// Bind the texture
			glBindTexture(GL_TEXTURE_2D, mesh.GetAlbedoTexture().mID);

			glActiveTexture(GL_TEXTURE0 + 1);
			// Set the sampler to the correct texture unit
			glUniform1i(glGetUniformLocation(_shader.mID, "texture_normal"), 1);
			// Bind the texture
			glBindTexture(GL_TEXTURE_2D, mesh.GetNormalTexture().mID);

			// Draw mesh
			glBindVertexArray(mesh.GetVAO());
			glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(mesh.GetIndices().size()), GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);

			// Set everything back to default
			glActiveTexture(GL_TEXTURE0);
		}
	}
}