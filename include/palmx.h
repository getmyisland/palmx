/**********************************************************************************************
*
*   palmx - simple easy-to-use library to make PS1-like games
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

#ifndef PALMX_H
#define PALMX_H

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

#include <string>
#include <vector>
#include <map>

namespace palmx
{
    //----------------------------------------------------------------------------------
    // Enumerators Definition
    //----------------------------------------------------------------------------------

    enum KeyCode
    {
        KEY_ESCAPE,
        KEY_W,
        KEY_A,
        KEY_S,
        KEY_D
    };

    //----------------------------------------------------------------------------------
    // Structures Definition
    //----------------------------------------------------------------------------------

    struct Transform
    {
        glm::vec3 position { glm::vec3(0, 0, 0) };
        glm::vec3 rotation { glm::vec3(0, 0, 0) }; // Pitch, Yaw, Roll
        glm::vec3 scale { glm::vec3(1, 1, 1) };
    };

    struct Camera
    {
        Transform transform;
        float zoom { 45 };
    };

    struct Shader
    {
        unsigned int id;
    };

    struct Vertex
    {
        glm::vec3 position;
        glm::vec3 normal;
        glm::vec2 tex_coords;
        glm::vec3 tangent;
        glm::vec3 bitangent;
        int bone_ids[4];
        float weights[4];
    };

    struct Color
    {
        float r;
        float g;
        float b;
        float a;
    };

    struct Texture
    {
        unsigned int id;
    };

    struct Character
    {
        Texture texture; // The glyph texture
        glm::ivec2   size; // Size of glyph
        glm::ivec2   bearing; // Offset from baseline to left/top of glyph
        unsigned int advance; // Horizontal offset to advance to next glyph
    };

    struct Font
    {
        std::map<char, Character> characters;
    };

    struct Mesh
    {
        std::vector<Vertex>       vertices;
        std::vector<unsigned int> indices;
        Texture albedo_texture;
        Texture normal_texture;

        unsigned int vao;
        unsigned int vbo;
        unsigned int ebo;
    };

    struct Model
    {
        Transform transform;
        std::vector<Mesh> meshes;
    };

    struct Primitive
    {
        Transform transform;
        Color color { 1.0f, 1.0f, 1.0f, 1.0f };

        unsigned int vao;
        unsigned int vbo;
        unsigned int ebo;
    };

    struct Rigidbody
    {
        glm::vec3 velocity;
        glm::vec3 force;
        float mass { 10 };
        bool is_dynamic { true };
    };

    struct Dimension
    {
        int width;
        int height;
    };

    //------------------------------------------------------------------------------------
    // Global Variables Definition
    //------------------------------------------------------------------------------------

    const Color color_lightgray = { 200.0f / 255.0f, 200.0f / 255.0f, 200.0f / 255.0f, 1.0f };
    const Color color_gray = { 130.0f / 255.0f, 130.0f / 255.0f, 130.0f / 255.0f, 1.0f };
    const Color color_darkgray = { 80.0f / 255.0f, 80.0f / 255.0f, 80.0f / 255.0f, 1.0f };
    const Color color_yellow = { 253.0f / 255.0f, 249.0f / 255.0f, 0.0f, 1.0f };
    const Color color_gold = { 1.0f, 203.0f / 255.0f, 0.0f, 1.0f };
    const Color color_orange = { 1.0f, 161.0f / 255.0f, 0.0f, 1.0f };
    const Color color_pink = { 1.0f, 109.0f / 255.0f, 194.0f / 255.0f, 1.0f };
    const Color color_red = { 230.0f / 255.0f, 41.0f / 255.0f, 55.0f / 255.0f, 1.0f };
    const Color color_maroon = { 190.0f / 255.0f, 33.0f / 255.0f, 55.0f / 255.0f, 1.0f };
    const Color color_green = { 0.0f, 228.0f / 255.0f, 48.0f / 255.0f, 1.0f };
    const Color color_lime = { 0.0f, 158.0f / 255.0f, 47.0f / 255.0f, 1.0f };
    const Color color_darkgreen = { 0.0f, 117.0f / 255.0f, 44.0f / 255.0f, 1.0f };
    const Color color_skyblue = { 102.0f / 255.0f, 191.0f / 255.0f, 1.0f, 1.0f };
    const Color color_blue = { 0.0f, 121.0f / 255.0f, 241.0f / 255.0f, 1.0f };
    const Color color_darkblue = { 0.0f, 82.0f / 255.0f, 172.0f / 255.0f, 1.0f };
    const Color color_purple = { 200.0f / 255.0f, 122.0f / 255.0f, 1.0f, 1.0f };
    const Color color_violet = { 135.0f / 255.0f, 60.0f / 255.0f, 190.0f / 255.0f, 1.0f };
    const Color color_darkpurple = { 112.0f / 255.0f, 31.0f / 255.0f, 126.0f / 255.0f, 1.0f };
    const Color color_beige = { 211.0f / 255.0f, 176.0f / 255.0f, 131.0f / 255.0f, 1.0f };
    const Color color_brown = { 127.0f / 255.0f, 106.0f / 255.0f, 79.0f / 255.0f, 1.0f };
    const Color color_darkbrown = { 76.0f / 255.0f, 63.0f / 255.0f, 47.0f / 255.0f, 1.0f };
    const Color color_white = { 1.0f, 1.0f, 1.0f, 1.0f };
    const Color color_black = { 0.0f, 0.0f, 0.0f, 1.0f };
    const Color color_blank = { 0.0f, 0.0f, 0.0f, 0.0f };
    const Color color_magenta = { 1.0f, 0.0f, 1.0f, 1.0f };

    //----------------------------------------------------------------------------------
    // Core
    //----------------------------------------------------------------------------------

    extern void Init(std::string title, int width, int height); // Initialize window and OpenGL context
    extern void Exit(); // Close window and unload OpenGL context
    extern bool IsExitRequested(); // Was glfw requested to close the window
    extern void RequestExit(); // Request to close the window

    extern Dimension GetWindowDimension();

    extern float GetTime();
    extern float GetDeltaTime();

    //----------------------------------------------------------------------------------
    // Input
    //----------------------------------------------------------------------------------

    extern void CollectInput();
    extern void SetExitKey(KeyCode key_code); // Default is KEY_ESCAPE
    extern bool IsKeyDown(KeyCode key_code);
    extern bool IsKeyPressed(KeyCode key_code);
    extern bool IsKeyUp(KeyCode key_code);
    extern glm::vec2 GetMouseOffset();
    extern glm::vec2 GetMouseWheelOffset();

    extern void ShowCursor();
    extern void HideCursor();
    extern void UnlockCursor();
    extern void LockCursor();

    //----------------------------------------------------------------------------------
    // Graphics
    //----------------------------------------------------------------------------------

    extern void BeginDrawing(Camera& camera); // Setup canvas (framebuffer) to start drawing
    extern void EndDrawing(); // End canvas drawing and swap buffers
    extern void SetBackground(Color color);

    extern Shader LoadShader(const std::string& vertex_shader_file_path, const std::string& fragment_shader_file_path);
    extern Shader LoadShaderFromMemory(const std::string& vertex_shader_source, const std::string& fragment_shader_source);
    extern int GetShaderUniformLocation(Shader& shader, const std::string& uniform_name);

    extern Texture LoadTexture(const std::string& file_path);

    extern Model LoadModel(const std::string& file_path);
    extern void DrawModel(Model& model);

    extern Primitive CreateCube();
    extern void DrawPrimitive(Primitive& primitive);

    //----------------------------------------------------------------------------------
    // User Interface
    //----------------------------------------------------------------------------------

    extern Font LoadDefaultFont();
    extern Font LoadFont(const std::string& file_path);
    extern void SetFont(const Font& new_font);

    extern void DrawText(const std::string& text, glm::vec2 position, float scale, const Color& color = color_white);
    extern void DrawSprite(const Texture& texture, glm::vec2 position, glm::vec2 size, const Color& color = color_white);

    //----------------------------------------------------------------------------------
    // Filesystem
    //----------------------------------------------------------------------------------

    extern std::string GetRootDirectory();
    extern std::string GetAbsolutePath(const std::string relative_path);
}

#endif // PALMX_H