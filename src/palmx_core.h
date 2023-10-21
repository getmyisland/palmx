#ifndef PALMX_CORE_H
#define PALMX_CORE_H

#include <GLFW/glfw3.h>

#include <string>

namespace palmx
{
    struct PxData
    {
        bool init { false };

        std::string title;
        GLFWwindow* window;
    };

    extern PxData px_data;
}

#endif // PALMX_CORE_H