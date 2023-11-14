#include <glad/glad.h> // Needs to be included first

#include "palmx_graphics.h"
#include "palmx_core.h"

#include <palmx.h>
#include <palmx_debug.h>
#include <palmx_math.h>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#ifndef STBI_INCLUDE_STB_IMAGE_H
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>
#endif

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
    std::string default_vertex_shader_source = R"(
		#version 330 core

		layout (location = 0) in vec3 aPos;
		layout (location = 1) in vec3 aNormal;
		layout (location = 2) in vec2 aTexCoord;

		out vec2 texCoord;

		uniform mat4 mesh;
		uniform mat4 view;
		uniform mat4 projection;

		void main()
		{
			gl_Position = projection * view * mesh * vec4(aPos, 1.0);
			texCoord = aTexCoord;
		}
	)";

    std::string default_fragment_shader_source = R"(
		#version 330 core

		in vec3 color;
		in vec2 texCoord;

		out vec4 FragColor;  
				
		uniform sampler2D texture_albedo;
		uniform sampler2D texture_normal;

		void main()
		{
			FragColor = texture(texture_albedo, texCoord);
		}
	)";

    std::string fullscreen_quad_vertex_shader = R"(
		#version 330 core

		layout (location = 0) in vec3 aPos;
		layout (location = 1) in vec2 aTexCoord;

		out vec2 TexCoord;

		void main() {
			gl_Position = vec4(aPos, 1.0);
			TexCoord = aTexCoord;
		}
	)";

    std::string fullscreen_quad_fragment_shader = R"(
		#version 330 core

		in vec2 TexCoord;

		out vec4 FragColor;

		uniform sampler2D renderTexture;

		void main() {
			FragColor = texture(renderTexture, TexCoord);
		}
	)";

    GLuint render_texture;
    GLuint render_texture_framebuffer;
    // PS1 display was 256x224px
    const unsigned int render_texture_width { 256 };
    const unsigned int render_texture_heigth { 224 };

    GLuint fullscreen_quad_vertex_buffer;
    GLuint fullscreen_quad_vertex_array;
    Shader fullscreen_quad_shader;

    Shader default_shader;

    Color background_color { color_black };

    enum ShaderType
    {
        VERTEX,
        FRAGMENT,
        PROGRAM
    };

    void SetupGraphics()
    {
        if (!px_data.init)
        {
            LogError("palmx not initialized");
            return;
        }

        // Load all OpenGL function pointers
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            return;
        }

        glEnable(GL_CULL_FACE);
        glEnable(GL_DEPTH_TEST);

        // Create a render texture and framebuffer the scene can render to before being displayed
        glGenFramebuffers(1, &render_texture_framebuffer);
        glBindFramebuffer(GL_FRAMEBUFFER, render_texture_framebuffer);

        glGenTextures(1, &render_texture);
        glBindTexture(GL_TEXTURE_2D, render_texture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, render_texture_width, render_texture_heigth, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        GLuint render_texture_renderbuffer;
        glGenRenderbuffers(1, &render_texture_renderbuffer);
        glBindRenderbuffer(GL_RENDERBUFFER, render_texture_renderbuffer);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, render_texture_width, render_texture_heigth);
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

        default_shader = LoadShaderFromMemory(default_vertex_shader_source, default_fragment_shader_source);
        fullscreen_quad_shader = LoadShaderFromMemory(fullscreen_quad_vertex_shader, fullscreen_quad_fragment_shader);
    }

    void BeginDrawing(Camera& camera)
    {
        if (!px_data.init)
        {
            LogError("palmx not initialized");
            return;
        }

        glClearColor(background_color.r, background_color.g, background_color.b, background_color.a);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Always render the scene at a lower resolution to emulate the ps1 screen
        // Everything below will now be rendered to the render texture instead of the screen directly
        glBindFramebuffer(GL_FRAMEBUFFER, render_texture_framebuffer);
        glViewport(0, 0, render_texture_width, render_texture_heigth);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(default_shader.id);

        int framebuffer_width, framebuffer_height;
        glfwGetFramebufferSize(px_data.window, &framebuffer_width, &framebuffer_height);
        glm::mat4 projection = glm::perspective(glm::radians(camera.zoom), static_cast<float>(framebuffer_width) / static_cast<float>(framebuffer_height), 0.1f, 100.0f);
        glUniformMatrix4fv(GetShaderUniformLocation(default_shader, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

        glm::mat4 view = glm::lookAt(camera.transform.position, camera.transform.position + Vector3Forward(camera.transform.rotation), Vector3Up(camera.transform.rotation));
        glUniformMatrix4fv(GetShaderUniformLocation(default_shader, "view"), 1, GL_FALSE, glm::value_ptr(view));
    }

    void EndDrawing()
    {
        if (!px_data.init)
        {
            LogError("palmx not initialized");
            return;
        }

        Dimension window_dimension = GetWindowDimension();
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glViewport(0, 0, window_dimension.width, window_dimension.heigth);

        glUseProgram(fullscreen_quad_shader.id);

        glBindTexture(GL_TEXTURE_2D, render_texture);
        glBindVertexArray(fullscreen_quad_vertex_array);

        glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

        glBindVertexArray(0);
        glBindTexture(GL_TEXTURE_2D, 0);

        glfwSwapBuffers(px_data.window);
        glfwPollEvents();
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
                LogError("Shader compilation failed for type " + std::to_string(type) + "\n" + std::string(info_log));
            }
        }
        else
        {
            glGetProgramiv(object, GL_LINK_STATUS, &success);
            if (!success)
            {
                glGetProgramInfoLog(object, 1024, NULL, info_log);
                LogError("Shader program linking failed\n" + std::string(info_log));
            }
        }
    }

    Shader CompileShader(std::string vertex_shader_source, std::string fragment_shader_source)
    {
        const GLchar* vertex_shader_code = vertex_shader_source.c_str();
        const GLchar* fragment_shader_code = fragment_shader_source.c_str();

        GLuint vertex_shader;
        GLuint fragment_shader;
        // Vertex Shader
        vertex_shader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex_shader, 1, &vertex_shader_code, NULL);
        glCompileShader(vertex_shader);
        CheckShaderCompileErrors(vertex_shader, VERTEX);
        // Fragment Shader
        fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment_shader, 1, &fragment_shader_code, NULL);
        glCompileShader(fragment_shader);
        CheckShaderCompileErrors(fragment_shader, FRAGMENT);
        // Shader Program
        unsigned int id = glCreateProgram();
        glAttachShader(id, vertex_shader);
        glAttachShader(id, fragment_shader);
        glLinkProgram(id);
        CheckShaderCompileErrors(id, PROGRAM);
        // Delete the shaders as they're linked into our program now and no longer necessary
        glDeleteShader(vertex_shader);
        glDeleteShader(fragment_shader);

        return Shader(id);
    }

    Shader LoadShader(const std::string& vertex_shader_file_path, const std::string& fragment_shader_file_path)
    {
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
            LogError("Shader file not successfully read at paths: " + std::string(vertex_shader_file_path) + " and " + std::string(fragment_shader_file_path));
        }

        const GLchar* vertex_shader_code_c = vertex_shader_code.c_str();
        const GLchar* fragment_shader_code_c = fragment_shader_code.c_str();

        return CompileShader(vertex_shader_code_c, fragment_shader_code_c);
    }

    Shader LoadShaderFromMemory(const std::string& vertex_shader_source, const std::string& fragment_shader_source)
    {
        return CompileShader(vertex_shader_source, fragment_shader_source);
    }

    int GetShaderUniformLocation(Shader& shader, const std::string& uniform_name)
    {
        GLint location = glGetUniformLocation(shader.id, uniform_name.c_str());
        if (location == -1)
        {
            LogError("Shader Uniform Location " + uniform_name + " not found");
        }
        return location;
    }

    Texture LoadTexture(const std::string& file_path)
    {
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
            LogError("Failed to load texture at path: " + std::string(file_path));
            stbi_image_free(data);
        }

        return { texture_id };
    }

    Mesh ProcessMesh(aiMesh* ai_mesh, const aiScene* ai_scene, std::string directory)
    {
        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;

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

            vertices.push_back(vertex);
        }

        // Process indices
        for (unsigned int i = 0; i < ai_mesh->mNumFaces; i++)
        {
            aiFace face = ai_mesh->mFaces[i];
            for (unsigned int j = 0; j < face.mNumIndices; j++)
                indices.push_back(face.mIndices[j]);
        }

        // Load Materials
        std::string material_name = ai_scene->mMaterials[ai_mesh->mMaterialIndex]->GetName().C_Str();
        Texture albedo_texture = LoadTexture(std::string(directory + "/" + material_name + "_texture_albedo.jpg").c_str());
        Texture normal_texture = LoadTexture(std::string(directory + "/" + material_name + "_texture_normal.jpg").c_str());

        unsigned int vao, vbo, ebo;

        // Create buffers/arrays
        glGenVertexArrays(1, &vao);
        glGenBuffers(1, &vbo);
        glGenBuffers(1, &ebo);

        glBindVertexArray(vao);
        // Load data into vertex buffers
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        // A great thing about structs is that their memory layout is sequential for all its items.
        // The effect is that we can simply pass a pointer to the struct and it translates perfectly to a glm::vec3/2 array which
        // Again translates to 3/2 floats which translates to a byte array.
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

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

        Mesh mesh;
        mesh.vertices = vertices;
        mesh.indices = indices;
        mesh.albedo_texture = albedo_texture;
        mesh.normal_texture = normal_texture;
        mesh.vao = vao;
        mesh.vbo = vbo;
        mesh.ebo = ebo;

        return mesh;
    }

    std::vector<Mesh> ProcessNode(aiNode* ai_node, const aiScene* ai_scene, std::string directory)
    {
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

    Model LoadModel(std::string file_path)
    {
        Assimp::Importer importer;
        const aiScene* ai_scene = importer.ReadFile(file_path, aiProcess_Triangulate | aiProcess_FlipUVs);

        if (!ai_scene || ai_scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !ai_scene->mRootNode)
        {
            auto error = importer.GetErrorString();
            LogError(std::string("ASSIMP::") + error);
            return Model();
        }

        Model model;
        model.meshes = ProcessNode(ai_scene->mRootNode, ai_scene, std::string(file_path).substr(0, std::string(file_path).find_last_of('/')));
        return model;
    }

    void DrawModel(Model& model)
    {
        for (Mesh& mesh : model.meshes)
        {
            // Render the mesh
            glm::mat4 mesh_mat4 = glm::mat4(1.0f);
            mesh_mat4 = glm::translate(mesh_mat4, static_cast<glm::vec3>(model.transform.position));
            mesh_mat4 = glm::scale(mesh_mat4, static_cast<glm::vec3>(model.transform.scale));
            glUniformMatrix4fv(GetShaderUniformLocation(default_shader, "mesh"), 1, GL_FALSE, glm::value_ptr(mesh_mat4));

            glActiveTexture(GL_TEXTURE0 + 0);
            // Set the sampler to the correct texture unit
            glUniform1i(GetShaderUniformLocation(default_shader, "texture_albedo"), 0);
            // Bind the texture
            glBindTexture(GL_TEXTURE_2D, mesh.albedo_texture.id);

            glActiveTexture(GL_TEXTURE0 + 1);
            // Set the sampler to the correct texture unit
            glUniform1i(GetShaderUniformLocation(default_shader, "texture_normal"), 1);
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
}