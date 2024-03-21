/**********************************************************************************************
*
*   palmx - ui rendering for text and sprites, with functions for initialization and drawing
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

#include "palmx_engine.h"
#include "palmx_default_font.h"

#include <glm/glm.hpp>
#include <glm/trigonometric.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <ft2build.h>
#include FT_FREETYPE_H

#include <fstream>
#include <sstream>
#include <iostream>
#include <map>

namespace palmx
{
	Font font;
	Shader font_shader;

	GLuint text_vao, text_vbo;

	Shader sprite_shader;
	GLuint sprite_vao, sprite_vbo, sprite_ebo;

	void InitUserInterface()
	{
		PALMX_ASSERT(px_data.init, "palmx not initialized");

		std::string text_vertex_shader = R"(
            #version 330 core
            
            layout (location = 0) in vec4 a_Vertex; // <vec2 pos, vec2 tex>
            
			out vec2 v_TexCoord;

            uniform mat4 u_Projection;

            void main()
            {
                gl_Position = u_Projection * vec4(a_Vertex.xy, 0.0, 1.0);
                v_TexCoord = a_Vertex.zw;
            }
        )";

		std::string text_fragment_shader = R"(
            #version 330 core

            in vec2 v_TexCoord;

            out vec4 o_FragColor;

            uniform sampler2D u_Text;
            uniform vec4 u_Color;

            void main()
            {    
                o_FragColor = u_Color * vec4(1.0, 1.0, 1.0, texture(u_Text, v_TexCoord).r);
            }
        )";

		font_shader = LoadShaderFromMemory(text_vertex_shader, text_fragment_shader);

		// FIXME: What if window dimensions change?
		Dimension window_dimension = GetWindowDimension();
		glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(window_dimension.width), 0.0f, static_cast<float>(window_dimension.height));
		glUseProgram(font_shader.id);
		glUniformMatrix4fv(glGetUniformLocation(font_shader.id, "u_Projection"), 1, GL_FALSE, glm::value_ptr(projection));

		font = LoadDefaultFont();

		glGenVertexArrays(1, &text_vao);
		glGenBuffers(1, &text_vbo);

		glBindVertexArray(text_vao);

		glBindBuffer(GL_ARRAY_BUFFER, text_vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

		std::string sprite_vertex_shader = R"(
            #version 330 core
            
            layout (location = 0) in vec3 a_Position;

            out vec2 v_TexCoord;

            uniform mat4 u_Model;
            uniform mat4 u_Projection;

            void main()
            {
                gl_Position = u_Projection * u_Model * vec4(a_Position, 1.0);
                v_TexCoord = (a_Position.xy + vec2(1.0, 1.0)) / 2.0;
            }
        )";

		std::string sprite_fragment_shader = R"(
            #version 330 core

            in vec2 v_TexCoord;

            out vec4 o_FragColor;

            uniform vec4 u_Color;
            uniform sampler2D u_Texture;

            void main() {
                o_FragColor = u_Color * texture(u_Texture, v_TexCoord);
            }
        )";

		sprite_shader = LoadShaderFromMemory(sprite_vertex_shader, sprite_fragment_shader);

		// Reuse projection matrix from above
		glUseProgram(sprite_shader.id);
		glUniformMatrix4fv(glGetUniformLocation(sprite_shader.id, "u_Projection"), 1, GL_FALSE, glm::value_ptr(projection));

		float sprite_vertices[] = {
			// positions
			1.0f,  1.0f, 0.0f,   // top right
			1.0f, -1.0f, 0.0f,   // bottom right
			-1.0f, -1.0f, 0.0f,   // bottom left
			-1.0f,  1.0f, 0.0f    // top left
		};

		unsigned int sprite_indices[] = {
			0, 1, 3,   // first triangle
			1, 2, 3    // second triangle
		};

		glGenVertexArrays(1, &sprite_vao);
		glGenBuffers(1, &sprite_vbo);
		glGenBuffers(1, &sprite_ebo);

		glBindVertexArray(sprite_vao);

		glBindBuffer(GL_ARRAY_BUFFER, sprite_vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(sprite_vertices), sprite_vertices, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, sprite_ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(sprite_indices), sprite_indices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

	Font LoadFontFromMemory(const unsigned char* font_data, unsigned int font_size)
	{
		PALMX_ASSERT(px_data.init, "palmx not initialized");

		std::map<char, Character> characters;

		if (font_data == nullptr || font_size == 0)
		{
			PALMX_ERROR("Failed to load font from memory: Invalid data");
			return { characters };
		}

		FT_Library ft;
		if (FT_Init_FreeType(&ft))
		{
			PALMX_ERROR("Could not init FreeType Library");
			return { characters };
		}

		FT_Face face;
		if (FT_New_Memory_Face(ft, font_data, font_size, 0, &face))
		{
			PALMX_ERROR("Failed to load font from memory");
			FT_Done_FreeType(ft);
			return { characters };
		}
		else
		{
			FT_Set_Pixel_Sizes(face, 0, 48);

			// Disable byte-alignment restriction
			glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

			// Load first 128 characters of ASCII set
			for (unsigned char c = 0; c < 128; c++)
			{
				// Load character glyph
				if (FT_Load_Char(face, c, FT_LOAD_RENDER))
				{
					PALMX_ERROR("Failed to load glyph");
					continue;
				}

				// Generate texture
				unsigned int texture_id;
				glGenTextures(1, &texture_id);
				glBindTexture(GL_TEXTURE_2D, texture_id);
				glTexImage2D(
					GL_TEXTURE_2D,
					0,
					GL_RED,
					face->glyph->bitmap.width,
					face->glyph->bitmap.rows,
					0,
					GL_RED,
					GL_UNSIGNED_BYTE,
					face->glyph->bitmap.buffer
				);

				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

				// Store character for later use
				Character character = {
					{texture_id},
					glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
					glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
					static_cast<unsigned int>(face->glyph->advance.x)
				};

				characters.insert(std::pair<char, Character>(c, character));
			}

			glBindTexture(GL_TEXTURE_2D, 0);
		}

		// Destroy FreeType once finished
		FT_Done_Face(face);
		FT_Done_FreeType(ft);

		return { characters };
	}

	Font LoadDefaultFont()
	{
		return LoadFontFromMemory(default_font_ttf, default_font_ttf_len);
	}

	Font LoadFont(const std::string& file_path)
	{
		std::vector<unsigned char> font_data;

		if (!file_path.empty())
		{
			// Read font file into memory
			std::ifstream file(file_path, std::ios::binary);
			if (file)
			{
				file.seekg(0, std::ios::end);
				font_data.resize(file.tellg());
				file.seekg(0, std::ios::beg);
				file.read(reinterpret_cast<char*>(font_data.data()), font_data.size());
				file.close();
			}
			else
			{
				PALMX_ERROR("Failed to load font file at path: " << file_path);
				return Font();
			}
		}
		else
		{
			PALMX_ERROR("Failed to load font file at path: empty path provided");
			return Font();
		}

		return LoadFontFromMemory(font_data.data(), font_data.size());
	}

	void SetFont(const Font& new_font)
	{
		font = new_font;
	}

	void DrawString(const std::string& text, glm::vec2 position, float scale, const Color& color)
	{
		PALMX_ASSERT(px_data.init, "palmx not initialized");

		// Activate corresponding render state	
		glUseProgram(font_shader.id);
		glUniform4f(glGetUniformLocation(font_shader.id, "u_Color"), color.r, color.g, color.b, color.a);
		glActiveTexture(GL_TEXTURE0);
		glBindVertexArray(text_vao);

		// Iterate through all characters
		std::string::const_iterator c;
		for (c = text.begin(); c != text.end(); c++)
		{
			Character ch = font.characters[*c];

			float xpos = position.x + ch.bearing.x * scale;
			float ypos = position.y - (ch.size.y - ch.bearing.y) * scale;

			float w = ch.size.x * scale;
			float h = ch.size.y * scale;

			// Update VBO for each character
			float vertices[6][4] = {
				{ xpos,     ypos + h,   0.0f, 0.0f },
				{ xpos,     ypos,       0.0f, 1.0f },
				{ xpos + w, ypos,       1.0f, 1.0f },

				{ xpos,     ypos + h,   0.0f, 0.0f },
				{ xpos + w, ypos,       1.0f, 1.0f },
				{ xpos + w, ypos + h,   1.0f, 0.0f }
			};

			// Render glyph texture over quad
			glBindTexture(GL_TEXTURE_2D, ch.texture.id);

			// Update content of VBO memory
			glBindBuffer(GL_ARRAY_BUFFER, text_vbo);
			glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);

			glBindBuffer(GL_ARRAY_BUFFER, 0);
			// Render Quad
			glDrawArrays(GL_TRIANGLES, 0, 6);

			// Advance cursors for next glyph (note that advance is number of 1/64 pixels)
			position.x += (ch.advance >> 6) * scale; // Bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))
		}

		glBindVertexArray(0);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void DrawSprite(const Sprite& sprite)
	{
		PALMX_ASSERT(px_data.init, "palmx not initialized");

		// Only works when face culling is disabled or else the sprite will be invisible
		glDisable(GL_CULL_FACE);

		glUseProgram(sprite_shader.id);

		glUniformMatrix4fv(glGetUniformLocation(sprite_shader.id, "u_Model"), 1, GL_FALSE, glm::value_ptr(sprite.transform.GetTransform()));
		glUniform4f(glGetUniformLocation(sprite_shader.id, "u_Color"), sprite.color.r, sprite.color.g, sprite.color.b, sprite.color.a);

		glActiveTexture(GL_TEXTURE0);
		glUniform1i(glGetUniformLocation(sprite_shader.id, "u_Texture"), 0);
		glBindTexture(GL_TEXTURE_2D, sprite.texture.id);

		glBindVertexArray(sprite_vao);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, sprite_ebo);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		// Enable face culling again
		glEnable(GL_CULL_FACE);
	}
}