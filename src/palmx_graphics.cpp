/**********************************************************************************************
*
*   palmx - graphic context management
*
*	MIT License
*
*   Copyright (c) 2023 Maximilian Fischer (getmyisland)
*
*   Permission is hereby granted, free of charge, to any person obtaining a copy
*   of this software and associated documentation files (the "Software"), to deal
*   in the Software without restriction, including without limitation the rights
*   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
*   copies of the Software, and to permit persons to whom the Software is
*   furnished to do so, subject to the following conditions:
*
*   The above copyright notice and this permission notice shall be included in all
*   copies or substantial portions of the Software.
*
*   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
*   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
*   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
*   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
*   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
*   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
*   SOFTWARE.
*
**********************************************************************************************/

#include "pxpch.h"
#include <glad/glad.h>

#include "palmx_core.h"
#include "palmx_graphics.h"

#include <palmx.h>
#include <palmx_math.h>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <GLFW/glfw3.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

namespace palmx
{
	GLuint render_texture;
	GLuint render_texture_framebuffer;

	// PlayStation 1 display was 320x240px or 640x480px
	const unsigned int render_texture_width{ 320 };
	const unsigned int render_texture_height{ 240 };

	GLuint fullscreen_quad_vertex_buffer;
	GLuint fullscreen_quad_vertex_array;
	Shader fullscreen_quad_shader;

	Shader model_shader;
	Shader primitive_shader;

	Color background_color{ color_black };

	enum class ShaderType
	{
		VERTEX,
		FRAGMENT,
		PROGRAM
	};

	void graphics::Init()
	{
		PALMX_ASSERT(px_data.init, "palmx not initialized");

		// Load all OpenGL function pointers
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		PALMX_ASSERT(status, "Failed to initialize Glad!");

		PALMX_INFO("OpenGL Info:");
		PALMX_INFO("Vendor: " << glGetString(GL_VENDOR));
		PALMX_INFO("Renderer: " << glGetString(GL_RENDERER));
		PALMX_INFO("Version: " << glGetString(GL_VERSION));

		glEnable(GL_CULL_FACE);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		// Create a render texture and framebuffer the scene can render to before being displayed
		glGenFramebuffers(1, &render_texture_framebuffer);
		glBindFramebuffer(GL_FRAMEBUFFER, render_texture_framebuffer);

		glGenTextures(1, &render_texture);
		glBindTexture(GL_TEXTURE_2D, render_texture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, render_texture_width, render_texture_height, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		GLuint render_texture_renderbuffer;
		glGenRenderbuffers(1, &render_texture_renderbuffer);
		glBindRenderbuffer(GL_RENDERBUFFER, render_texture_renderbuffer);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, render_texture_width, render_texture_height);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, render_texture_renderbuffer);

		glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, render_texture, 0);

		GLenum draw_buffers[1] = { GL_COLOR_ATTACHMENT0 };
		glDrawBuffers(1, draw_buffers);

		GLfloat quad_vertices[] = {
			-1.0f, -1.0f, 0.0f, 0.0f, 0.0f, // Bottom-left vertex
			1.0f, -1.0f, 0.0f, 1.0f, 0.0f,  // Bottom-right vertex
			1.0f, 1.0f, 0.0f, 1.0f, 1.0f,   // Top-right vertex
			-1.0f, 1.0f, 0.0f, 0.0f, 1.0f    // Top-left vertex
		};

		glGenVertexArrays(1, &fullscreen_quad_vertex_array);
		glGenBuffers(1, &fullscreen_quad_vertex_buffer);

		glBindVertexArray(fullscreen_quad_vertex_array);
		glBindBuffer(GL_ARRAY_BUFFER, fullscreen_quad_vertex_buffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(quad_vertices), quad_vertices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
		glEnableVertexAttribArray(1);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

		std::string fullscreen_quad_vertex_shader = R"(
            #version 330 core

            layout (location = 0) in vec3 a_Position;
            layout (location = 1) in vec2 a_TexCoord;

            out vec2 v_TexCoord;

            void main() {
                gl_Position = vec4(a_Position, 1.0);
                v_TexCoord = a_TexCoord;
            }
        )";

		std::string fullscreen_quad_fragment_shader = R"(
            #version 330 core

            in vec2 v_TexCoord;

            out vec4 o_FragColor;

            uniform sampler2D u_FullscreenTexture;

            void main() {
                o_FragColor = texture(u_FullscreenTexture, v_TexCoord);
            }
        )";

		fullscreen_quad_shader = LoadShaderFromMemory(fullscreen_quad_vertex_shader, fullscreen_quad_fragment_shader);

		std::string model_vertex_shader_source = R"(
            #version 330 core

            layout (location = 0) in vec3 a_Position;
            layout (location = 1) in vec3 a_Normal;
            layout (location = 2) in vec2 a_TexCoord;

            noperspective out vec2 v_TexCoord;

            uniform mat4 u_Model;
            uniform mat4 u_View;
            uniform mat4 u_Projection;

			uniform vec3 u_ModelPosition;
			const float jitterAmount = 0.005;

            void main()
            {
				// Calculate world space position of the vertex
				vec3 worldPosition = (u_Model * vec4(a_Position, 1.0)).xyz + u_ModelPosition;

				// Apply vertex jitter
				vec3 jitter = vec3(
					fract(sin(dot(worldPosition, vec3(12.9898, 78.233, 45.543))) * 43758.5453),
					fract(cos(dot(worldPosition, vec3(4.898, 7.23, 32.789))) * 23421.631),
					0.0
				) * jitterAmount;

				vec3 jitterPosition = a_Position + jitter;

				gl_Position = u_Projection * u_View * u_Model * vec4(jitterPosition, 1.0);

                v_TexCoord = a_TexCoord;
            }
        )";

		// TODO: Normal texture rendering
		std::string model_fragment_shader_source = R"(
            #version 330 core

            noperspective in vec2 v_TexCoord;

            out vec4 o_FragColor;  
                    
            uniform sampler2D u_TextureAlbedo;
            uniform sampler2D u_TextureNormal;

            void main()
            {
                o_FragColor = texture(u_TextureAlbedo, v_TexCoord);
            }
        )";

		model_shader = LoadShaderFromMemory(model_vertex_shader_source, model_fragment_shader_source);

		std::string primitive_vertex_shader_source = R"(
            #version 330 core

            layout (location = 0) in vec3 a_Position;

            uniform mat4 u_Model;
            uniform mat4 u_View;
            uniform mat4 u_Projection;

            void main()
            {
                gl_Position = u_Projection * u_View * u_Model * vec4(a_Position, 1.0);
            }
        )";

		std::string primitive_fragment_shader_source = R"(
            #version 330 core

            out vec4 o_FragColor;  
                    
            uniform vec4 u_Color;

            void main()
            {
                o_FragColor = u_Color;
            }
        )";

		primitive_shader = LoadShaderFromMemory(primitive_vertex_shader_source, primitive_fragment_shader_source);
	}

	void BeginDrawing(Camera& camera)
	{
		PALMX_ASSERT(px_data.init, "palmx not initialized");

		glfwPollEvents();

		glClearColor(background_color.r, background_color.g, background_color.b, background_color.a);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Render the scene at a lower resolution to emulate the PS1 screen
		// Everything below will now be rendered to the render texture instead of the screen directly
		glBindFramebuffer(GL_FRAMEBUFFER, render_texture_framebuffer);
		glViewport(0, 0, render_texture_width, render_texture_height);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		int framebuffer_width, framebuffer_height;
		glfwGetFramebufferSize(px_data.window, &framebuffer_width, &framebuffer_height);
		glm::mat4 projection = glm::perspective(glm::radians(camera.zoom), static_cast<float>(framebuffer_width) / static_cast<float>(framebuffer_height), 0.1f, 100.0f);
		glm::mat4 view = glm::lookAt(camera.transform.position, camera.transform.position + Vector3Forward(camera.transform.rotation), Vector3Up(camera.transform.rotation));

		glUseProgram(model_shader.id);
		glUniformMatrix4fv(glGetUniformLocation(model_shader.id, "u_Projection"), 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(glGetUniformLocation(model_shader.id, "u_View"), 1, GL_FALSE, glm::value_ptr(view));

		glUseProgram(primitive_shader.id);
		glUniformMatrix4fv(glGetUniformLocation(primitive_shader.id, "u_Projection"), 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(glGetUniformLocation(primitive_shader.id, "u_View"), 1, GL_FALSE, glm::value_ptr(view));
	}

	void EndDrawing()
	{
		PALMX_ASSERT(px_data.init, "palmx not initialized");

		// Reset the viewport to the size of the window
		auto window_size = GetWindowSize();
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glViewport(0, 0, window_size.x, window_size.y);

		glUseProgram(fullscreen_quad_shader.id);

		glBindTexture(GL_TEXTURE_2D, render_texture);
		glBindVertexArray(fullscreen_quad_vertex_array);

		// Draw the render texture onto the entire screen
		glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

		glBindVertexArray(0);
		glBindTexture(GL_TEXTURE_2D, 0);

		glfwSwapBuffers(px_data.window);
	}

	void SetBackground(Color color)
	{
		background_color = color;
	}

	void CheckShaderCompileErrors(GLuint object, ShaderType type)
	{
		GLint success;
		char info_log[1024];
		if (type != ShaderType::PROGRAM)
		{
			glGetShaderiv(object, GL_COMPILE_STATUS, &success);
			if (!success)
			{
				glGetShaderInfoLog(object, 1024, NULL, info_log);
				PALMX_ERROR((type == ShaderType::VERTEX ? "Vertex" : "Fragment") << " shader linking failed:\n" << info_log);
			}
		}
		else
		{
			glGetProgramiv(object, GL_LINK_STATUS, &success);
			if (!success)
			{
				glGetProgramInfoLog(object, 1024, NULL, info_log);
				PALMX_ERROR("Program Linking failed.\n" << info_log);
			}
		}
	}

	Shader CompileShader(std::string vertex_shader_source, std::string fragment_shader_source)
	{
		PALMX_ASSERT(px_data.init, "palmx not initialized");

		const GLchar* vertex_shader_code = vertex_shader_source.c_str();
		const GLchar* fragment_shader_code = fragment_shader_source.c_str();

		GLuint vertex_shader;
		GLuint fragment_shader;
		// Vertex Shader
		vertex_shader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex_shader, 1, &vertex_shader_code, NULL);
		glCompileShader(vertex_shader);
		CheckShaderCompileErrors(vertex_shader, ShaderType::VERTEX);
		// Fragment Shader
		fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment_shader, 1, &fragment_shader_code, NULL);
		glCompileShader(fragment_shader);
		CheckShaderCompileErrors(fragment_shader, ShaderType::FRAGMENT);
		// Shader Program
		unsigned int id = glCreateProgram();
		glAttachShader(id, vertex_shader);
		glAttachShader(id, fragment_shader);
		glLinkProgram(id);
		CheckShaderCompileErrors(id, ShaderType::PROGRAM);
		// Delete the shaders as they're linked into our program now and no longer necessary
		glDeleteShader(vertex_shader);
		glDeleteShader(fragment_shader);

		return Shader(id);
	}

	Shader LoadShader(const std::string& vertex_shader_file_path, const std::string& fragment_shader_file_path)
	{
		PALMX_ASSERT(px_data.init, "palmx not initialized");

		// Retrieve the vertex/fragment source code from filePath
		std::string vertex_shader_code;
		std::string fragment_shader_code;
		std::ifstream vertex_shader_file;
		std::ifstream fragment_shader_file;
		// Ensures ifstream objects can throw exceptions:
		vertex_shader_file.exceptions(std::ifstream::badbit);
		fragment_shader_file.exceptions(std::ifstream::badbit);
		try
		{
			// Open files
			vertex_shader_file.open(vertex_shader_file_path);
			fragment_shader_file.open(fragment_shader_file_path);
			std::stringstream vertex_shader_stream, fragment_shader_stream;
			// Read file's buffer contents into streams
			vertex_shader_stream << vertex_shader_file.rdbuf();
			fragment_shader_stream << fragment_shader_file.rdbuf();
			// close file handlers
			vertex_shader_file.close();
			fragment_shader_file.close();
			// Convert stream into string
			vertex_shader_code = vertex_shader_stream.str();
			fragment_shader_code = fragment_shader_stream.str();
		}
		catch (std::ifstream::failure e)
		{
			PALMX_ERROR("Shader file not successfully read:\n" << e.what()
				<< "\nVertex shader path: " << vertex_shader_file_path
				<< "\nFragment shader path: " << fragment_shader_file_path
			);
			return Shader();
		}

		const GLchar* vertex_shader_code_c = vertex_shader_code.c_str();
		const GLchar* fragment_shader_code_c = fragment_shader_code.c_str();

		return CompileShader(vertex_shader_code_c, fragment_shader_code_c);
	}

	Shader LoadShaderFromMemory(const std::string& vertex_shader_source, const std::string& fragment_shader_source)
	{
		PALMX_ASSERT(px_data.init, "palmx not initialized");

		return CompileShader(vertex_shader_source, fragment_shader_source);
	}

	Texture LoadTexture(const std::string& file_path)
	{
		PALMX_ASSERT(px_data.init, "palmx not initialized");

		unsigned int texture_id;
		glGenTextures(1, &texture_id);

		int width, height, num_components;
		unsigned char* data = stbi_load(file_path.c_str(), &width, &height, &num_components, 0);
		if (data)
		{
			GLenum format = GL_RGB;
			if (num_components == 1)
				format = GL_RED;
			else if (num_components == 3)
				format = GL_RGB;
			else if (num_components == 4)
				format = GL_RGBA;

			glBindTexture(GL_TEXTURE_2D, texture_id);
			glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

			stbi_image_free(data);
		}
		else
		{
			PALMX_ERROR("Failed to load texture at path: " << file_path);
			stbi_image_free(data);
		}

		return { texture_id };
	}

	Mesh ProcessMesh(aiMesh* ai_mesh, const aiScene* ai_scene, std::string directory)
	{
		PALMX_ASSERT(px_data.init, "palmx not initialized");

		Mesh mesh = {};

		for (unsigned int i = 0; i < ai_mesh->mNumVertices; i++)
		{
			Vertex vertex;

			// Process vertex positions, normals and texture coordinates
			glm::vec3 vec3;
			vec3.x = ai_mesh->mVertices[i].x;
			vec3.y = ai_mesh->mVertices[i].y;
			vec3.z = ai_mesh->mVertices[i].z;
			vertex.position = vec3;

			vec3.x = ai_mesh->mNormals[i].x;
			vec3.y = ai_mesh->mNormals[i].y;
			vec3.z = ai_mesh->mNormals[i].z;
			vertex.normal = vec3;

			if (ai_mesh->mTextureCoords[0]) // Does the ai_mesh contain texture coordinates?
			{
				glm::vec2 vec2;
				vec2.x = ai_mesh->mTextureCoords[0][i].x;
				vec2.y = ai_mesh->mTextureCoords[0][i].y;
				vertex.tex_coords = vec2;
			}
			else
			{
				vertex.tex_coords = glm::vec2(0.0f, 0.0f);
			}

			mesh.vertices.push_back(vertex);
		}

		// Process indices
		for (unsigned int i = 0; i < ai_mesh->mNumFaces; i++)
		{
			aiFace face = ai_mesh->mFaces[i];
			for (unsigned int j = 0; j < face.mNumIndices; j++)
				mesh.indices.push_back(face.mIndices[j]);
		}

		// Load Materials
		std::string material_name = ai_scene->mMaterials[ai_mesh->mMaterialIndex]->GetName().C_Str();
		mesh.albedo_texture = LoadTexture(std::string(directory + "/" + material_name + "_texture_albedo.png"));
		mesh.normal_texture = LoadTexture(std::string(directory + "/" + material_name + "_texture_normal.png"));

		// Create buffers/arrays
		glGenVertexArrays(1, &mesh.vao);
		glGenBuffers(1, &mesh.vbo);
		glGenBuffers(1, &mesh.ebo);

		glBindVertexArray(mesh.vao);
		// Load data into vertex buffers
		glBindBuffer(GL_ARRAY_BUFFER, mesh.vbo);
		// A great thing about structs is that their memory layout is sequential for all its items.
		// The effect is that we can simply pass a pointer to the struct and it translates perfectly to a glm::vec3/2 array which
		// Again translates to 3/2 floats which translates to a byte array.
		glBufferData(GL_ARRAY_BUFFER, mesh.vertices.size() * sizeof(Vertex), &mesh.vertices[0], GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh.indices.size() * sizeof(unsigned int), &mesh.indices[0], GL_STATIC_DRAW);

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

		return mesh;
	}

	std::vector<Mesh> ProcessNode(aiNode* ai_node, const aiScene* ai_scene, std::string directory)
	{
		PALMX_ASSERT(px_data.init, "palmx not initialized");

		std::vector<Mesh> meshes = std::vector<Mesh>();

		// Process all the ai_node's meshes (if any)
		for (unsigned int i = 0; i < ai_node->mNumMeshes; i++)
		{
			aiMesh* ai_mesh = ai_scene->mMeshes[ai_node->mMeshes[i]];
			meshes.push_back(ProcessMesh(ai_mesh, ai_scene, directory));
		}

		// Then do the same for each of its children
		for (unsigned int i = 0; i < ai_node->mNumChildren; i++)
		{
			std::vector<Mesh> child_meshes = ProcessNode(ai_node->mChildren[i], ai_scene, directory);
			meshes.insert(meshes.end(), child_meshes.begin(), child_meshes.end());
		}

		return meshes;
	}

	Model LoadModel(const std::string& file_path)
	{
		PALMX_ASSERT(px_data.init, "palmx not initialized");

		unsigned int flags =
			aiProcess_CalcTangentSpace | // calculate tangents and bitangents if possible
			aiProcess_JoinIdenticalVertices | // join identical vertices/ optimize indexing
			//aiProcess_ValidateDataStructure  | // perform a full validation of the loader's output
			aiProcess_Triangulate | // Ensure all verticies are triangulated (each 3 vertices are triangle)
			//aiProcess_ConvertToLeftHanded | // convert everything to D3D left handed space (by default right-handed, for OpenGL)
			aiProcess_SortByPType | // ?
			aiProcess_ImproveCacheLocality | // improve the cache locality of the output vertices
			aiProcess_RemoveRedundantMaterials | // remove redundant materials
			aiProcess_FindDegenerates | // remove degenerated polygons from the import
			aiProcess_FindInvalidData | // detect invalid model data, such as invalid normal vectors
			aiProcess_GenUVCoords | // convert spherical, cylindrical, box and planar mapping to proper UVs
			aiProcess_TransformUVCoords | // preprocess UV transformations (scaling, translation ...)
			aiProcess_FindInstances | // search for instanced meshes and remove them by references to one master
			aiProcess_LimitBoneWeights | // limit bone weights to 4 per vertex
			aiProcess_OptimizeMeshes | // join small meshes, if possible;
			//aiProcess_PreTransformVertices | //-- fixes the transformation issue.
			//aiProcess_SplitByBoneCount | // split meshes with too many bones. Necessary for our (limited) hardware skinning shader
			aiProcess_FlipUVs | // flip all UVs or else textures will be messed up
			0;

		Assimp::Importer importer;
		const aiScene* ai_scene = importer.ReadFile(file_path, flags);

		if (!ai_scene || ai_scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !ai_scene->mRootNode)
		{
			auto error = importer.GetErrorString();
			PALMX_ERROR("Failed to load model with Assimp\n" << error);
			return Model();
		}

		Model model;
		model.meshes = ProcessNode(ai_scene->mRootNode, ai_scene, std::string(file_path).substr(0, std::string(file_path).find_last_of('/')));
		return model;
	}

	void DrawModel(Model& model)
	{
		PALMX_ASSERT(px_data.init, "palmx not initialized");

		glUseProgram(model_shader.id);

		for (Mesh& mesh : model.meshes)
		{
			glUniformMatrix4fv(glGetUniformLocation(model_shader.id, "u_Model"), 1, GL_FALSE, glm::value_ptr(model.transform.GetTransform()));
			glUniform3fv(glGetUniformLocation(model_shader.id, "u_ModelPosition"), 3, glm::value_ptr(model.transform.position));

			glActiveTexture(GL_TEXTURE0 + 0);
			// Set the sampler to the correct texture unit
			glUniform1i(glGetUniformLocation(model_shader.id, "u_TextureAlbedo"), 0);
			// Bind the texture
			glBindTexture(GL_TEXTURE_2D, mesh.albedo_texture.id);

			glActiveTexture(GL_TEXTURE0 + 1);
			// Set the sampler to the correct texture unit
			glUniform1i(glGetUniformLocation(model_shader.id, "u_TextureNormal"), 1);
			// Bind the texture
			glBindTexture(GL_TEXTURE_2D, mesh.normal_texture.id);

			// Draw mesh
			glBindVertexArray(mesh.vao);
			glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(mesh.indices.size()), GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);

			// Set everything back to default
			glActiveTexture(GL_TEXTURE0);
		}
	}

	Primitive CreateCube()
	{
		PALMX_ASSERT(px_data.init, "palmx not initialized");

		Primitive cube = {};

		GLfloat vertices[] = {
			-0.5f, -0.5f, -0.5f,
			0.5f, -0.5f, -0.5f,
			0.5f,  0.5f, -0.5f,
			0.5f,  0.5f, -0.5f,
			-0.5f,  0.5f, -0.5f,
			-0.5f, -0.5f, -0.5f,

			-0.5f, -0.5f,  0.5f,
			0.5f, -0.5f,  0.5f,
			0.5f,  0.5f,  0.5f,
			0.5f,  0.5f,  0.5f,
			-0.5f,  0.5f,  0.5f,
			-0.5f, -0.5f,  0.5f,

			-0.5f,  0.5f,  0.5f,
			-0.5f,  0.5f, -0.5f,
			-0.5f, -0.5f, -0.5f,
			-0.5f, -0.5f, -0.5f,
			-0.5f, -0.5f,  0.5f,
			-0.5f,  0.5f,  0.5f,

			0.5f,  0.5f,  0.5f,
			0.5f,  0.5f, -0.5f,
			0.5f, -0.5f, -0.5f,
			0.5f, -0.5f, -0.5f,
			0.5f, -0.5f,  0.5f,
			0.5f,  0.5f,  0.5f,

			-0.5f, -0.5f, -0.5f,
			0.5f, -0.5f, -0.5f,
			0.5f, -0.5f,  0.5f,
			0.5f, -0.5f,  0.5f,
			-0.5f, -0.5f,  0.5f,
			-0.5f, -0.5f, -0.5f,

			-0.5f,  0.5f, -0.5f,
			0.5f,  0.5f, -0.5f,
			0.5f,  0.5f,  0.5f,
			0.5f,  0.5f,  0.5f,
			-0.5f,  0.5f,  0.5f,
			-0.5f,  0.5f, -0.5f
		};

		glGenVertexArrays(1, &cube.vao);
		glBindVertexArray(cube.vao);

		glGenBuffers(1, &cube.vbo);
		glBindBuffer(GL_ARRAY_BUFFER, cube.vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

		return cube;
	}

	// TODO: Add more primitives
	// TODO: Support primitives with indices
	void DrawPrimitive(Primitive& primitive)
	{
		PALMX_ASSERT(px_data.init, "palmx not initialized");

		// Only works when face culling is disabled or else some faces will be invisible
		glDisable(GL_CULL_FACE);

		glUseProgram(primitive_shader.id);
		glUniform4f(glGetUniformLocation(primitive_shader.id, "u_Color"), primitive.color.r, primitive.color.g, primitive.color.b, primitive.color.a);

		glUniformMatrix4fv(glGetUniformLocation(primitive_shader.id, "u_Model"), 1, GL_FALSE, glm::value_ptr(primitive.transform.GetTransform()));

		glBindVertexArray(primitive.vao);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);

		// Enable it again
		glEnable(GL_CULL_FACE);
	}
}