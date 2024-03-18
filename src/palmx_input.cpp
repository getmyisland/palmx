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
		bool is_first_mouse_input{ true };
		bool mouse_callback_this_frame{ false };
		glm::vec2 last_mouse_pos;
		glm::vec2 mouse_offset;
		bool mouse_wheel_callback_this_frame{ false };
		glm::vec2 mouse_wheel_offset;
	};

	Mouse mouse;

	void MouseCallback(GLFWwindow* window, double y_pos_in, double x_pos_in)
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

	void ScrollCallback(GLFWwindow* window, double x_offset, double y_offset)
	{
		mouse.mouse_wheel_offset = glm::vec2(static_cast<float>(x_offset), static_cast<float>(y_offset));

		mouse.mouse_wheel_callback_this_frame = true;
	}

	void InitInput()
	{
		if (!px_data.init)
		{
			PALMX_CRITICAL("palmx not initialized");
			return;
		}

		glfwSetCursorPosCallback(px_data.window, MouseCallback);
		glfwSetScrollCallback(px_data.window, ScrollCallback);
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
		if (!px_data.init)
		{
			PALMX_CRITICAL("palmx not initialized");
			return false;
		}

		auto state = glfwGetKey(px_data.window, static_cast<int32_t>(key));
		return state == GLFW_PRESS;
	}

	bool IsMouseButtonPressed(const input::MouseCode button)
	{
		if (!px_data.init)
		{
			PALMX_CRITICAL("palmx not initialized");
			return false;
		}

		auto state = glfwGetMouseButton(px_data.window, static_cast<int32_t>(button));
		return state == GLFW_PRESS;
	}

	glm::vec2 GetMousePosition()
	{
		if (!px_data.init)
		{
			PALMX_CRITICAL("palmx not initialized");
			return glm::vec2();
		}

		double xpos, ypos;
		glfwGetCursorPos(px_data.window, &xpos, &ypos);

		return { (float)xpos, (float)ypos };
	}

	float GetMouseX()
	{
		if (!px_data.init)
		{
			PALMX_CRITICAL("palmx not initialized");
			return 0;
		}

		return GetMousePosition().x;
	}

	float GetMouseY()
	{
		if (!px_data.init)
		{
			PALMX_CRITICAL("palmx not initialized");
			return 0;
		}

		return GetMousePosition().y;
	}

    void ShowCursor()
    {
        if (!px_data.init)
        {
            PALMX_CRITICAL("palmx not initialized");
            return;
        }

        glfwSetInputMode(px_data.window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }

    void HideCursor()
    {
        if (!px_data.init)
        {
            PALMX_CRITICAL("palmx not initialized");
            return;
        }

        glfwSetInputMode(px_data.window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
    }

    void UnlockCursor()
    {
        if (!px_data.init)
        {
            PALMX_CRITICAL("palmx not initialized");
            return;
        }

        glfwSetInputMode(px_data.window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }

    void LockCursor()
    {
        if (!px_data.init)
        {
            PALMX_CRITICAL("palmx not initialized");
            return;
        }

        glfwSetInputMode(px_data.window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }
}