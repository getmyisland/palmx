#include <glad/glad.h> // Needs to be included first

#include "palmx_ui.h"
#include "palmx_graphics.h"
#include "palmx_core.h"

#include <palmx.h>
#include <palmx_debug.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <ft2build.h>
#include FT_FREETYPE_H

#include <map>

namespace palmx
{
    /// All state information relevant to a character as loaded using FreeType
    struct Character
    {
        unsigned int texture_id; // ID handle of the glyph texture
        glm::ivec2   size; // Size of glyph
        glm::ivec2   bearing; // Offset from baseline to left/top of glyph
        unsigned int advance; // Horizontal offset to advance to next glyph
    };

    Shader font_shader;
    std::map<GLchar, Character> characters;
    unsigned int vao, vbo;

    void SetupUserInterface()
    {
        if (!px_data.init)
        {
            LogError("palmx not initialized");
            return;
        }

        std::string text_vertex_shader = R"(
            #version 330 core
            
            layout (location = 0) in vec4 vertex; // <vec2 pos, vec2 tex>
            out vec2 TexCoords;

            uniform mat4 projection;

            void main()
            {
                gl_Position = projection * vec4(vertex.xy, 0.0, 1.0);
                TexCoords = vertex.zw;
            }
        )";

        std::string text_fragment_shader = R"(
            #version 330 core

            in vec2 TexCoords;
            out vec4 color;

            uniform sampler2D text;
            uniform vec3 textColor;

            void main()
            {    
                vec4 sampled = vec4(1.0, 1.0, 1.0, texture(text, TexCoords).r);
                color = vec4(textColor, 1.0) * sampled;
            }
        )";

        font_shader = LoadShaderFromMemory(text_vertex_shader, text_fragment_shader);

        Dimension window_dimension = GetWindowDimension();
        glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(window_dimension.width), 0.0f, static_cast<float>(window_dimension.height));
        glUseProgram(font_shader.id);
        glUniformMatrix4fv(glGetUniformLocation(font_shader.id, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

        FT_Library ft;
        if (FT_Init_FreeType(&ft))
        {
            LogError("Could not init FreeType Library");
            return;
        }

        std::string font_name = GetAbsolutePath("/resources/VCR_OSD_MONO.ttf");
        if (font_name.empty())
        {
            LogError("Failed to load default font path");
            return;
        }

        FT_Face face;
        if (FT_New_Face(ft, font_name.c_str(), 0, &face))
        {
            LogError("Failed to load default font");
            return;
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
                    LogError("Failed to load glyph");
                    continue;
                }

                // Generate texture
                unsigned int texture;
                glGenTextures(1, &texture);
                glBindTexture(GL_TEXTURE_2D, texture);
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
                    texture,
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

        glGenVertexArrays(1, &vao);
        glGenBuffers(1, &vbo);
        glBindVertexArray(vao);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

    void DrawText(const std::string& text, float x, float y, float scale, const Color color)
    {
        // Activate corresponding render state	
        glUseProgram(font_shader.id);
        glUniform3f(glGetUniformLocation(font_shader.id, "textColor"), color.r, color.g, color.b);
        glActiveTexture(GL_TEXTURE0);
        glBindVertexArray(vao);

        // Iterate through all characters
        std::string::const_iterator c;
        for (c = text.begin(); c != text.end(); c++)
        {
            Character ch = characters[*c];

            float xpos = x + ch.bearing.x * scale;
            float ypos = y - (ch.size.y - ch.bearing.y) * scale;

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
            glBindTexture(GL_TEXTURE_2D, ch.texture_id);

            // Update content of VBO memory
            glBindBuffer(GL_ARRAY_BUFFER, vbo);
            glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);

            glBindBuffer(GL_ARRAY_BUFFER, 0);
            // Render Quad
            glDrawArrays(GL_TRIANGLES, 0, 6);

            // Advance cursors for next glyph (note that advance is number of 1/64 pixels)
            x += (ch.advance >> 6) * scale; // Bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))
        }

        glBindVertexArray(0);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}