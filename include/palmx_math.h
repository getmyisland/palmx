/**********************************************************************************************
*
*   palmx - Math functions for various vector/matrix operations.
*
*   Copyright (c) 2023 Maximilian Fischer (getmyisland)
*
*   Licensed under the MIT License. See LICENSE.md for full details.
*
**********************************************************************************************/

#ifndef PALMX_MATH_H
#define PALMX_MATH_H

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

namespace palmx
{
    //----------------------------------------------------------------------------------
    // Vector 3 Functions
    //----------------------------------------------------------------------------------
    extern glm::vec3 Vector3Forward(glm::vec3 vec3);
    extern glm::vec3 Vector3Right(glm::vec3 vec3);
    extern glm::vec3 Vector3Up(glm::vec3 vec3);
}

#endif // PALMX_MATH_H