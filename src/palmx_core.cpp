#include "palmx_core.h"

#include <palmx.h>
#include <palmx_debug.h>

#include "palmx_input.h"
#include "palmx_graphics.h"
#include "palmx_ui.h"

namespace palmx
{
    PxData px_data { NULL };

    void FramebufferSizeCallback(GLFWwindow* window, int width, int height)
    {
        // Make sure the viewport matches the new window dimensions; note that width and 
        // Height will be significantly larger than specified on retina displays.
        glViewport(0, 0, width, height);
    }

    void Init(std::string title, int width, int height)
    {
        if (px_data.init)
        {
            LogError("palmx cannot be initialized twice");
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
            LogError("Could not create glfw window");
            return;
        }

        glfwMakeContextCurrent(px_data.window);
        glfwSetFramebufferSizeCallback(px_data.window, FramebufferSizeCallback);

        SetupInput();
        SetupGraphics();
        SetupUserInterface();
    }

    void Exit()
    {
        glfwTerminate();
    }

    bool IsExitRequested()
    {
        if (!px_data.init)
        {
            LogError("palmx not initialized");
            return false;
        }

        return glfwWindowShouldClose(px_data.window);
    }

    void RequestExit()
    {
        glfwSetWindowShouldClose(px_data.window, true);
    }

    Dimension GetWindowDimension()
    {
        Dimension window_dimension = {};

        if (!px_data.init)
        {
            LogError("palmx not initialized");
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