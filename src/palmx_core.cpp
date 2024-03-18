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
#include "palmx_engine.h"

namespace palmx
{
    PxData px_data { NULL };

    void FramebufferSizeCallback(GLFWwindow* window, int width, int height)
    {
        // Make sure the viewport matches the new window dimensions; note that width and 
        // height will be significantly larger than specified on retina displays.
        glViewport(0, 0, width, height);
    }

    void Init(std::string title, int width, int height)
    {
        if (px_data.init)
        {
            PALMX_CRITICAL("palmx cannot be initialized twice")
            return;
        }

        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

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
        glfwSetFramebufferSizeCallback(px_data.window, FramebufferSizeCallback);

        InitInput();
        InitGraphics();
        InitUserInterface();
    }

    void Exit()
    {
        // TODO clean up other stuff as well (OpenGL)
        glfwTerminate();
    }

    bool IsExitRequested()
    {
        if (!px_data.init)
        {
            PALMX_CRITICAL("palmx not initialized");
            return false;
        }

        return glfwWindowShouldClose(px_data.window);
    }

    void RequestExit()
    {
        if (!px_data.init)
        {
            PALMX_CRITICAL("palmx not initialized");
            return;
        }

        glfwSetWindowShouldClose(px_data.window, true);
    }

    Dimension GetWindowDimension()
    {
        Dimension window_dimension = {};

        if (!px_data.init)
        {
            PALMX_CRITICAL("palmx not initialized");
            return window_dimension;
        }

        glfwGetWindowSize(px_data.window, &window_dimension.width, &window_dimension.height);

        return window_dimension;
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