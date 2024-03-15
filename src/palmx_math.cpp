/**********************************************************************************************
*
*   palmx - implementation of math functions
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
#include <palmx_math.h>

#include <glm/glm.hpp>

namespace palmx
{
    glm::vec3 Vector3Forward(glm::vec3 vec3)
    {
        glm::vec3 forward;
        forward.x = cos(glm::radians(vec3.y)) * cos(glm::radians(vec3.x));
        forward.y = sin(glm::radians(vec3.x));
        forward.z = sin(glm::radians(vec3.y)) * cos(glm::radians(vec3.x));
        return glm::normalize(forward);
    }

    glm::vec3 Vector3Right(glm::vec3 vec3)
    {
        return glm::normalize(glm::cross(Vector3Forward(vec3), glm::vec3(0, 1, 0)));
    }

    glm::vec3 Vector3Up(glm::vec3 vec3)
    {
        return glm::normalize(glm::cross(Vector3Right(vec3), Vector3Forward(vec3)));
    }
}