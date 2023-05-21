#include <GLFW/glfw3.h>

#include "ModuleManager.h"
#include <palm_engine/logger/Logger.h>

void framebuffer_size_callback(GLFWwindow* pWindow, int width, int height);

// Settings
const unsigned int cScreenWidth = 800;
const unsigned int cScreenHeight = 600;

int main()
{
    // Initialize and configure glfw
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // Create glfw window
    GLFWwindow* window = glfwCreateWindow(cScreenWidth, cScreenHeight, "Palm Engine", NULL, NULL);
    if (window == NULL)
    {
        PE_LOGGER_LOG(PE_ERROR, "Failed to create GLFW window");
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Start the actual game engine
    PE_MODULE_MANAGER.Run(window);

    glfwTerminate();
	return 0;
}

void framebuffer_size_callback(GLFWwindow* pWindow, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}