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

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

#include <cstdint>
#include <string>
#include <vector>
#include <map>

namespace palmx
{
	namespace input
	{
		using KeyCode = uint16_t;
		enum : KeyCode
		{
			// From glfw3.h
			Space = 32,
			Apostrophe = 39, /* ' */
			Comma = 44, /* , */
			Minus = 45, /* - */
			Period = 46, /* . */
			Slash = 47, /* / */

			D0 = 48, /* 0 */
			D1 = 49, /* 1 */
			D2 = 50, /* 2 */
			D3 = 51, /* 3 */
			D4 = 52, /* 4 */
			D5 = 53, /* 5 */
			D6 = 54, /* 6 */
			D7 = 55, /* 7 */
			D8 = 56, /* 8 */
			D9 = 57, /* 9 */

			Semicolon = 59, /* ; */
			Equal = 61, /* = */

			A = 65,
			B = 66,
			C = 67,
			D = 68,
			E = 69,
			F = 70,
			G = 71,
			H = 72,
			I = 73,
			J = 74,
			K = 75,
			L = 76,
			M = 77,
			N = 78,
			O = 79,
			P = 80,
			Q = 81,
			R = 82,
			S = 83,
			T = 84,
			U = 85,
			V = 86,
			W = 87,
			X = 88,
			Y = 89,
			Z = 90,

			LeftBracket = 91,  /* [ */
			Backslash = 92,  /* \ */
			RightBracket = 93,  /* ] */
			GraveAccent = 96,  /* ` */

			World1 = 161, /* non-US #1 */
			World2 = 162, /* non-US #2 */

			/* Function keys */
			Escape = 256,
			Enter = 257,
			Tab = 258,
			Backspace = 259,
			Insert = 260,
			Delete = 261,
			Right = 262,
			Left = 263,
			Down = 264,
			Up = 265,
			PageUp = 266,
			PageDown = 267,
			Home = 268,
			End = 269,
			CapsLock = 280,
			ScrollLock = 281,
			NumLock = 282,
			PrintScreen = 283,
			Pause = 284,
			F1 = 290,
			F2 = 291,
			F3 = 292,
			F4 = 293,
			F5 = 294,
			F6 = 295,
			F7 = 296,
			F8 = 297,
			F9 = 298,
			F10 = 299,
			F11 = 300,
			F12 = 301,
			F13 = 302,
			F14 = 303,
			F15 = 304,
			F16 = 305,
			F17 = 306,
			F18 = 307,
			F19 = 308,
			F20 = 309,
			F21 = 310,
			F22 = 311,
			F23 = 312,
			F24 = 313,
			F25 = 314,

			/* Keypad */
			KP0 = 320,
			KP1 = 321,
			KP2 = 322,
			KP3 = 323,
			KP4 = 324,
			KP5 = 325,
			KP6 = 326,
			KP7 = 327,
			KP8 = 328,
			KP9 = 329,
			KPDecimal = 330,
			KPDivide = 331,
			KPMultiply = 332,
			KPSubtract = 333,
			KPAdd = 334,
			KPEnter = 335,
			KPEqual = 336,

			LeftShift = 340,
			LeftControl = 341,
			LeftAlt = 342,
			LeftSuper = 343,
			RightShift = 344,
			RightControl = 345,
			RightAlt = 346,
			RightSuper = 347,
			Menu = 348
		};

		using MouseCode = uint16_t;
		enum : MouseCode
		{
			// From glfw3.h
			Button0 = 0,
			Button1 = 1,
			Button2 = 2,
			Button3 = 3,
			Button4 = 4,
			Button5 = 5,
			Button6 = 6,
			Button7 = 7,

			ButtonLast = Button7,
			ButtonLeft = Button0,
			ButtonRight = Button1,
			ButtonMiddle = Button2
		};
	}

	struct Transform
	{
		glm::vec3 position{ glm::vec3(0, 0, 0) };
		glm::vec3 rotation{ glm::vec3(0, 0, 0) }; // Pitch, Yaw, Roll
		glm::vec3 scale{ glm::vec3(1, 1, 1) };

		glm::mat4 GetTransform() const
		{
			glm::mat4 rot = glm::rotate(glm::mat4(1.0f), rotation.x, glm::vec3(1.0f, 0.0f, 0.0f))
				* glm::rotate(glm::mat4(1.0f), rotation.y, glm::vec3(0.0f, 1.0f, 0.0f))
				* glm::rotate(glm::mat4(1.0f), rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));

			return glm::translate(glm::mat4(1.0f), position)
				* rot
				* glm::scale(glm::mat4(1.0f), scale);
		}
	};

	struct Camera
	{
		Transform transform;
		float zoom{ 45 };
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

	struct Sprite
	{
		Transform transform;
		Texture texture;
		Color color = { 1.0f, 1.0f, 1.0f, 1.0f };
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
		Color color{ 1.0f, 1.0f, 1.0f, 1.0f };

		unsigned int vao;
		unsigned int vbo;
		unsigned int ebo;
	};

	struct Rigidbody
	{
		glm::vec3 velocity;
		glm::vec3 force;
		float mass{ 10 };
		bool is_dynamic{ true };
	};

	struct Dimension
	{
		int width;
		int height;
	};

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

	// Initialize window and OpenGL context.
	extern void Init(std::string title, int width, int height);
	// Close window and unload OpenGL context.
	extern void Exit();
	// Was glfw requested to close the window?
	extern bool IsExitRequested();
	// Request glfw to close the window.
	extern void RequestExit();

	extern Dimension GetWindowDimension();

	extern float GetTime();
	extern float GetDeltaTime();

	//----------------------------------------------------------------------------------
	// Input
	//----------------------------------------------------------------------------------

	extern bool IsKeyPressed(input::KeyCode key);

	extern bool IsMouseButtonPressed(input::MouseCode button);
	extern glm::vec2 GetMousePosition();
	extern glm::vec2 GetMouseOffset();
	extern float GetMouseX();
	extern float GetMouseY();
	extern glm::vec2 GetMouseWheelOffset();

	extern void ShowCursor();
	extern void HideCursor();
	extern void UnlockCursor();
	extern void LockCursor();

	//----------------------------------------------------------------------------------
	// Graphics
	//----------------------------------------------------------------------------------

	// Setup canvas (framebuffer) to start drawing
	extern void BeginDrawing(Camera& camera);
	// End canvas drawing and swap buffers
	extern void EndDrawing();

	extern void SetBackground(Color color);

	extern Shader LoadShader(const std::string& vertex_shader_file_path, const std::string& fragment_shader_file_path);
	extern Shader LoadShaderFromMemory(const std::string& vertex_shader_source, const std::string& fragment_shader_source);

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

	extern void DrawString(const std::string& text, glm::vec2 position, float scale, const Color& color = color_white);
	extern void DrawSprite(const Sprite& sprite);

	//----------------------------------------------------------------------------------
	// Filesystem
	//----------------------------------------------------------------------------------

	extern std::string GetCurrentDir();
	extern std::string GetResourceDir();
}

#endif // PALMX_H