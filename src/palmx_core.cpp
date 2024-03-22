/**********************************************************************************************
*
*   palmx - window management
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
#include "palmx_core.h"
#include "palmx_graphics.h"
#include "palmx_input.h"
#include "palmx_ui.h"

namespace palmx
{
	PxData px_data{ NULL };

	static void GLFWErrorCallback(int error, const char* description)
	{
		PALMX_ERROR("GLFW Error (" << error << ") " << description);
	}

	static void GLFWFramebufferSizeCallback(GLFWwindow* window, int width, int height)
	{
		// Make sure the viewport matches the new window dimensions; note that width and 
		// height will be significantly larger than specified on retina displays.
		glViewport(0, 0, width, height);

		ui::OnWindowResize(width, height);
	}

	void Init(std::string title, uint32_t width, uint32_t height)
	{
		PALMX_ASSERT(!px_data.init, "palmx cannot be initialized twice");

		int success = glfwInit();
		PALMX_ASSERT(success, "Could not initialize GLFW");
		glfwSetErrorCallback(GLFWErrorCallback);

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

		PALMX_INFO("Creating window " << title << " (" << width << ", " << height << ")");

		px_data.init = true;
		px_data.title = title;
		px_data.window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);

		if (px_data.window == nullptr)
		{
			glfwTerminate();
			PALMX_CRITICAL("Could not create glfw window");
			return;
		}

		glfwMakeContextCurrent(px_data.window);
		glfwSetFramebufferSizeCallback(px_data.window, GLFWFramebufferSizeCallback);

		input::Init();
		graphics::Init();
		ui::Init();

		// Manually call resize function as part of the initialization process
		ui::OnWindowResize(width, height);
	}

	void Exit()
	{
		glfwTerminate();
	}

	bool IsExitRequested()
	{
		PALMX_ASSERT(px_data.init, "palmx not initialized");

		return glfwWindowShouldClose(px_data.window);
	}

	void RequestExit()
	{
		PALMX_ASSERT(px_data.init, "palmx not initialized");

		PALMX_INFO("Exit requested");
		glfwSetWindowShouldClose(px_data.window, true);
	}

	glm::vec2 GetWindowSize()
	{
		PALMX_ASSERT(px_data.init, "palmx not initialized");

		int width, height;
		glfwGetWindowSize(px_data.window, &width, &height);

		return { width, height };
	}

	float GetTime()
	{
		return static_cast<float>(glfwGetTime());
	}

	float delta_time = 0.0f;
	float last_frame = 0.0f;
	float GetDeltaTime()
	{
		float current_frame = static_cast<float>(glfwGetTime());
		delta_time = current_frame - last_frame;
		last_frame = current_frame;

		return delta_time;
	}
}