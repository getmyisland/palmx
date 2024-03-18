/**********************************************************************************************
*
*   palmx - input management
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
#include "palmx_engine.h"

#include <GLFW/glfw3.h>

#include <unordered_map>

namespace palmx
{
	struct Mouse
	{
		bool is_first_mouse_input { true };
		bool mouse_callback_this_frame { false };
		glm::vec2 last_mouse_pos { glm::vec2() };
		glm::vec2 mouse_offset { glm::vec2() };
		bool mouse_wheel_callback_this_frame { false };
		glm::vec2 mouse_wheel_offset { glm::vec2() };
	};

	Mouse mouse;

	void GLFWMouseCallback(GLFWwindow* window, double y_pos_in, double x_pos_in)
	{
		float x_pos = static_cast<float>(-x_pos_in);
		float y_pos = static_cast<float>(-y_pos_in);

		if (mouse.is_first_mouse_input)
		{
			mouse.last_mouse_pos = glm::vec2(x_pos, y_pos);
			mouse.is_first_mouse_input = false;
		}

		float x_offset = x_pos - mouse.last_mouse_pos.x;
		float y_offset = mouse.last_mouse_pos.y - y_pos; // Reversed since y-Coordinates go from bottom to top

		mouse.last_mouse_pos = glm::vec2(x_pos, y_pos);
		mouse.mouse_offset = glm::vec2(x_offset, y_offset);

		mouse.mouse_callback_this_frame = true;
	}

	void GLFWScrollCallback(GLFWwindow* window, double x_offset, double y_offset)
	{
		mouse.mouse_wheel_offset = glm::vec2(static_cast<float>(x_offset), static_cast<float>(y_offset));

		mouse.mouse_wheel_callback_this_frame = true;
	}

	void InitInput()
	{
		PALMX_ASSERT(px_data.init, "palmx not initialized");

		glfwSetCursorPosCallback(px_data.window, GLFWMouseCallback);
		glfwSetScrollCallback(px_data.window, GLFWScrollCallback);
	}

	void ResetMouseOffset()
	{
		if (mouse.mouse_callback_this_frame)
		{
			mouse.mouse_callback_this_frame = false;
		}
		else
		{
			mouse.mouse_offset = glm::vec2();
		}
	}

	void ResetMouseWheelOffset()
	{
		if (mouse.mouse_wheel_callback_this_frame)
		{
			mouse.mouse_wheel_callback_this_frame = false;
		}
		else
		{
			mouse.mouse_wheel_offset = glm::vec2();
		}
	}

	glm::vec2 GetMouseOffset()
	{
		ResetMouseOffset();

		return mouse.mouse_offset;
	}

	glm::vec2 GetMouseWheelOffset()
	{
		ResetMouseWheelOffset();

		return mouse.mouse_wheel_offset;
	}

	bool IsKeyPressed(const input::KeyCode key)
	{
		PALMX_ASSERT(px_data.init, "palmx not initialized");

		auto state = glfwGetKey(px_data.window, static_cast<int32_t>(key));
		return state == GLFW_PRESS;
	}

	bool IsMouseButtonPressed(const input::MouseCode button)
	{
		PALMX_ASSERT(px_data.init, "palmx not initialized");

		auto state = glfwGetMouseButton(px_data.window, static_cast<int32_t>(button));
		return state == GLFW_PRESS;
	}

	glm::vec2 GetMousePosition()
	{
		PALMX_ASSERT(px_data.init, "palmx not initialized");

		double xpos, ypos;
		glfwGetCursorPos(px_data.window, &xpos, &ypos);

		return { (float)xpos, (float)ypos };
	}

	float GetMouseX()
	{
		PALMX_ASSERT(px_data.init, "palmx not initialized");

		return GetMousePosition().x;
	}

	float GetMouseY()
	{
		PALMX_ASSERT(px_data.init, "palmx not initialized");

		return GetMousePosition().y;
	}

	void ShowCursor()
	{
		PALMX_ASSERT(px_data.init, "palmx not initialized");

		glfwSetInputMode(px_data.window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}

	void HideCursor()
	{
		PALMX_ASSERT(px_data.init, "palmx not initialized");

		glfwSetInputMode(px_data.window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
	}

	void UnlockCursor()
	{
		PALMX_ASSERT(px_data.init, "palmx not initialized");

		glfwSetInputMode(px_data.window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}

	void LockCursor()
	{
		PALMX_ASSERT(px_data.init, "palmx not initialized");

		glfwSetInputMode(px_data.window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}
}